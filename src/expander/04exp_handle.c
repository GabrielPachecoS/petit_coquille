/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04exp_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:21:33 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/28 15:54:41 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_handle_expalnum(char *input, t_shell *shell)
{
	if (ft_isalpha(input[shell->len]) || input[shell->len] == '_')
	{
		shell->start = shell->len;
		shell->len++;
		while (ft_isalnum(input[shell->len]))
			shell->len++;
	}
	else
		return (input);
	return (ft_expandvar(input, shell));
}

static char	*ft_expand_brace_status(char *input, t_shell *shell)
{
	char	*var;

	if (input[shell->len] == '}')
	{
		write(2, "minishell: ${}: bad substitution", 33);
		shell->status = 1;
		return (input);
	}
	if (input[shell->len] == '?')
	{
		if (input[shell->len + 1] == '}' && input[shell->len + 2] == '"')
		{
			var = ft_itoa(shell->status);
			if (!var)
				return (NULL);
			free(var);
			return (input);
		}
		else
			return (input);
	}
	return (NULL);
}

char	*ft_handle_braces(char *input, t_shell *shell)
{
	char	*status_return;

	status_return = ft_expand_brace_status(input, shell);
	if (!status_return)
		return (status_return);
	if (ft_isalpha(input[shell->len]) || input[shell->len] == '_')
	{
		shell->start = shell->len;
		shell->len++;
		while (ft_isalnum(input[shell->len]))
			shell->len++;
	}
	if (input[shell->len] == '}')
		return (ft_expandvar(input, shell));
	else
		input = ft_substr(input, shell->start - 2, shell->len);
	return (status_return);
}

char	*ft_expandvar(char *input, t_shell *shell)
{
	char	*var;
	char	*aux;

	var = ft_substr(input, shell->start, shell->len - shell->start);
	if (!var)
		return (input);
	aux = env_var(shell->envp, var);
	free(var);
	if (!aux)
		return (input);
	input = ft_substr(input, shell->start, shell->len);
	return (input);
}

char	*ft_handle_expander(char *str_quoted, t_shell *shell)
{
	char	*tmp;

	if (!str_quoted)
		return (ft_strdup(""));
	if (str_quoted[0] == '"')
	{
		tmp = expand_double_quoted(str_quoted, shell);
		if (tmp)
			return (tmp);
	}
	tmp = ft_expand_str(str_quoted, shell);
	if (tmp)
		return (tmp);
	return (ft_strdup(""));
}
