/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:49:27 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/05 18:58:38 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

static int	ft_expquoted_continue(char *input, t_shell *shell, t_token **tokens)
{
	int	z;

	z = shell->len;
	if (ft_isalpha(input[z]) || input[z] == '_')
	{
		z++;
		while (ft_isalnum(input[z]))
			z++;
	}
	if (input[z] != '"')
		return (z);
	if (input[shell->len] == '{')
	{
		++shell->len;
		return (ft_handle_braces(input, shell, tokens));
	}
	shell->len = ft_handle_expalnum(input, shell, tokens);
	return (shell->len + 1);
}

static int	ft_expquoted(char *input, t_shell *shell, t_token **tokens)
{
	char	*var;

	if (input[shell->len] == '{')
		return (ft_handle_braces(input, shell, tokens));
	if (input[shell->len] == '?')
	{
		if (input[shell->len + 1] == '"')
		{
			var = ft_itoa(shell->status);
			if (!var)
				return (0);
			shell->start = ft_handle_word(var, 0, tokens);
			free(var);
			return (shell->len + 2);
		}
		return (++shell->len);
	}
	return (ft_expquoted_continue(input, shell, tokens));
}

static int	ft_handle_special_cases(char *input, t_shell *shell, t_token **tokens)
{
	char	*var;

	if (input[shell->len] == '?')
	{
		var = ft_itoa(shell->status);
		if (!var)
			return (0);
		shell->start = ft_handle_word(var, 0, tokens);
		free(var);
		return (shell->len + shell->start);
	}
	if (input[shell->len] == '{')
	{
		++shell->start;
		shell->len = ft_handle_braces(input, shell, tokens);
	}
	else
	{
		//printf("handle expanum %s e i %d\n", input, shell->len);
		shell->len = ft_handle_expalnum(input, shell, tokens);
	}
	return (shell->len);
}

int	ft_handle_expander(char *input, int i, t_shell *shell, t_token **tokens)
{
	shell->start = 0;
	shell->len = i;
	if (input[shell->len] == '"')
	{
		shell->len += 2;
		return (ft_expquoted(input, shell, tokens));
	}
	if (input[shell->len] == '$')
	{
		if (!input[shell->len + 1])
		{
			shell->status = 0;
			write(2, "$", 1);
			return (shell->len + 1);
		}
		shell->len++;
	}
	//printf("handle special cases nput %s e i %d\n\n", input, i);
	return (ft_handle_special_cases(input, shell, tokens));
}
