/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:49:27 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/01 18:18:59 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"


static int	ft_expquoted(char *input, int i, int j, t_shell *shell, t_token **tokens)
{
	printf(">> expquoted: input[%d] = '%c'\n", i, input[i]);
	char	*var;
	int	z;

	z = i;
	if (input[i] == '?')
	{
		if (input[i + 1] == '"')
		{
			printf(">> expanding $? com status = %d\n", shell->status);
			var = ft_itoa(shell->status);
			if (!var)
				return(0);
			j = ft_handle_word(var, 0, tokens);
			free(var);
			return (i + j);
		}
		else
			return(++i);
	}
	if ((ft_isalpha(input[z])) || input[i] == '_')
	{
		z++;
		while (ft_isalnum(input[z]))
		{
			printf(">> expquoted: input[%d] = '%c'\n", z, input[z]);
			z++;
		}
	}
	if (input[z] != '"')
		return(z);
	if (input[i] == '{')
		return (ft_handle_braces(input, ++i, j, shell, tokens));
	else
	{
		printf(">> expquoted enterind handle: input[%d] = '%c'\n", i, input[i]);
		i = (ft_handle_expalnum(input, i, j, shell, tokens));
		return (i + 1);
	}
}

int	ft_handle_expalnum(char *input, int i, int j, t_shell *shell, t_token **tokens)
{
	printf(">> expalnum: input[%d] = '%c'\n", i, input[i]);
	if ((ft_isalpha(input[i])) || input[i] == '_')
	{
		printf("entrou no if expalnum\n\n\n");
		j++;
		i++;
		printf(">> expalnum: input[%d] = '%c'\n", i, input[i]);
		while (ft_isalnum(input[i]))
		{
			printf(">> expalnum: input[%d] = '%c'\n", i, input[i]);
			j++;
			i++;
		}
	}
	else
	{
		return(i);
	}
	printf(">> expalnum: i = %d, j = %d\n", i, j);
	return (ft_expandvar(input, j, i - j, shell, tokens));
}

int	ft_handle_braces(char *input, int i, int j, t_shell *shell, t_token **tokens)
{
	printf(">> handle_braces: input[i] = '%c' (i = %d)\n", input[i], i);
	if (input[i] == '}')
	{
		write(2, "minishell: ${}: bad substitution", 33);
		shell->status = 1;
		return (i + 1);
	}
	if ((ft_isalpha(input[i])) || input[i] == '_')
	{
		j++;
		i++;
		while (ft_isalnum(input[i]))
		{
			j++;
			i++;
		}
	}
	printf(">> handle_braces: input[i] = '%c' (i = %d)\n", input[i], i);
	if (input[i] == '}')
		return (ft_expandvar(input, j, i - j, shell, tokens) + 1);
	else
		return (ft_handle_word(input, i - j - 2, tokens));
}
int	ft_expandvar(char *input, int len, int start, t_shell *shell, t_token **tokens)
{
	char	*var;

	printf(">> expandvar: input = %s len =%d, star = %d\n", input, len, start);
	var = ft_substr(input, start, len);
	printf("var = %s\n", var);
	if (!var)
		return(start + 1);
	var = env_var(shell->envp, var);
	ft_handle_word(var, 0, tokens);
	printf("saiu handle word\n");
	free(var);
	printf("len =%d, star = %d\n", len, start);
	return (len + start);
}

int ft_handle_expander(char *input, int i, t_shell *shell, t_token **tokens)
{
	char	*var;
	int		j;

	j = 0;
	printf(">> handle_expander: input[i] = '%c' (i = %d)\n", input[i], i);
	if (input[i] == '"')
		return (ft_expquoted(input, i + 2, j, shell, tokens));
	if (input[i] == '$')
	{
		if (!input[i + 1])
		{
			shell->status = 0;
			write(2, "$", 1);
			return(i + 1);
		}
		i++;
	}
	if (input[i] == '?')
	{
		printf(">> expanding $? com status = %d\n", shell->status);
		var = ft_itoa(shell->status);
		if (!var)
			return(0);
		j = ft_handle_word(var, 0, tokens);
		free(var);
		return (i + j);
	}
	if (input[i] == '{')
		i = ft_handle_braces(input, ++i, j, shell, tokens);
	else
		i = ft_handle_expalnum(input, i, j, shell, tokens);
	return (i);
}