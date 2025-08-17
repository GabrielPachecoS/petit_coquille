/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03exp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 21:33:48 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/16 21:34:13 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

static char	*ft_expquoted_continue(char *input, t_shell *shell, t_token **tokens)
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
		return (input);
	if (input[shell->len] == '{')
	{
		++shell->len;
		return (ft_handle_braces(input, shell, tokens));
	}
	input = ft_handle_expalnum(input, shell);
	return (input);
}

static char	*ft_expquoted(char *input, t_shell *shell, t_token **tokens)
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
			return (input);
		}
		return (input);
	}
	return (ft_expquoted_continue(input, shell, tokens));
}

static char	*ft_handle_special_cases(char *input, t_shell *shell, t_token **tokens)
{
	char	*var;

	if (input[shell->len] == '?')
	{
		printf("\n1)$? tem que entrar aqui = %s\n", input);
		var = ft_itoa(shell->status);
		if (!var)
			return (0);
		input = var;
		free(var);
		return (input);
	}
	if (input[shell->len] == '{')
	{
		++shell->start;
		input = ft_handle_braces(input, shell, tokens);
	}
	else
	{
		input = ft_handle_expalnum(input, shell);
	}
	return (input);
}

char	*ft_handle_expander(char *input, int i, t_shell *shell, t_token **tokens)
{
	shell->start = 0;
	shell->len = i;
	if (input[shell->len] == '"')
	{
		if (input[shell->len + 2] == '"')
		{
			shell->status = 0;
			write(1, "$", 1);
			return (input);
		}
		else
		{
			shell->len += 2;
			return (ft_expquoted(input, shell, tokens));
		}
	}
	if (input[shell->len] == '$')
	{
		if (!input[shell->len + 1])
		{
			shell->status = 0;
			write(1, "$", 1);
			return (input);
		}
		shell->len++;
	}
	return (ft_handle_special_cases(input, shell, tokens));
}