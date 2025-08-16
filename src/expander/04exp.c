/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04exp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:21:33 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/15 21:38:05 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

int	ft_handle_expalnum(char *input, t_shell *shell, t_token **tokens)
{
	if (ft_isalpha(input[shell->len]) || input[shell->len] == '_')
	{
		shell->start = shell->len;
		shell->len++;
		while (ft_isalnum(input[shell->len]))
			shell->len++;
	}
	else
		return (shell->len);
	return (ft_expandvar(input, shell, tokens) + 1);
}

static int	ft_expand_brace_status(char *input, t_shell *shell, t_token **tokens)
{
	char	*var;

	if (input[shell->len] == '}')
	{
		write(2, "minishell: ${}: bad substitution", 33);
		shell->status = 1;
		return (shell->len + 1);
	}
	if (input[shell->len] == '?')
	{
		if (input[shell->len + 1] == '}' && input[shell->len + 2] == '"')
		{
			var = ft_itoa(shell->status);
			if (!var)
				return (0);
			ft_handle_word(var, 0, tokens);
			free(var);
			return (shell->len + 2);
		}
		else
			return (++shell->len);
	}
	return (-1);
}

int	ft_handle_braces(char *input, t_shell *shell, t_token **tokens)
{
	int	status_return;

	status_return = ft_expand_brace_status(input, shell, tokens);
	if (status_return != -1)
		return (status_return);
	if (ft_isalpha(input[shell->len]) || input[shell->len] == '_')
	{
		shell->start = shell->len;
		shell->len++;
		while (ft_isalnum(input[shell->len]))
			shell->len++;
	}
	if (input[shell->len] == '}')
		return (ft_expandvar(input, shell, tokens) + 1);
	else
		return (ft_handle_word(input, shell->start - 2, tokens));
}

int	ft_expandvar(char *input, t_shell *shell, t_token **tokens)
{
	char	*var;
	char	*aux;

	var = ft_substr(input, shell->start, shell->len - shell->start);
	if (!var)
		return (shell->start + 1);
	aux = env_var(shell->envp, var);
	free(var);
	if (!aux)
		return (shell->len);
	ft_handle_word(aux, 0, tokens);
	return (shell->len);
}
