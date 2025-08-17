/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04exp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:21:33 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/16 21:35:10 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

char *ft_handle_expalnum(char *input, t_shell *shell)
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

static char	*ft_expand_brace_status(char *input, t_shell *shell, t_token **tokens)
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
			ft_handle_word(var, 0, tokens);
			free(var);
			return (input);
		}
		else
			return (input);
	}
	return (NULL);
}

char	*ft_handle_braces(char *input, t_shell *shell, t_token **tokens)
{
	char	*status_return;

	status_return = ft_expand_brace_status(input, shell, tokens);
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
	return(status_return);	
}

char	*ft_expandvar(char *input, t_shell *shell)
{
	char	*var;
	char	*aux;
	int		i;

	i = 0;
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
