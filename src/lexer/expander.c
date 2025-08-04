/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:49:27 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/04 18:04:06 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"


static int	ft_expquoted(char *input, int i, int j, t_shell *shell, t_token **tokens)
{
	char	*var;
	int	z;

	z = i;
	if (input[i] == '{')
		ft_handle_braces(input, i,  j, shell, tokens);
	if (input[i] == '?')
	{
		if (input[i + 1] == '"')
		{
			var = ft_itoa(shell->status);
			if (!var)
				return(0);
			j = ft_handle_word(var, 0, tokens);
			free(var);
			return (i + 2);
		}
		else
			return(++i);
	}
	if ((ft_isalpha(input[z])) || input[i] == '_')
	{
		z++;
		while (ft_isalnum(input[z]))
		{
			z++;
		}
	}
	if (input[z] != '"')
		return(z);
	if (input[i] == '{')
		return (ft_handle_braces(input, ++i, j, shell, tokens));
	else
	{
		i = (ft_handle_expalnum(input, i, j, shell, tokens));
		return (i + 1);
	}
}

int	ft_handle_expalnum(char *input, int i, int j, t_shell *shell, t_token **tokens)
{
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
	else
	{
		return(i);
	}
	return (ft_expandvar(input, j, i - j, shell, tokens));
}
static int	ft_expand_brace_status(char *input, int i, t_shell *shell, t_token **tokens)
{
	char	*var;

	if (input[i] == '}')
	{
		write(2, "minishell: ${}: bad substitution", 33);
		shell->status = 1;
		return (i + 1);
	}
	if (input[i] == '?')
	{
		if (input[i + 1] == '}' && input[i + 2] == '"')
		{
			var = ft_itoa(shell->status);
			if (!var)
				return (0);
			ft_handle_word(var, 0, tokens);
			free(var);
			return (i + 2);
		}
		else
			return (++i);
	}
	return (-1);
}

int	ft_handle_braces(char *input, int i, int j, t_shell *shell, t_token **tokens)
{
	int	status_return;

	status_return = ft_expand_brace_status(input, i, shell, tokens);
	if (status_return != -1)
		return (status_return);

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
	if (input[i] == '}')
		return (ft_expandvar(input, j, i - j, shell, tokens) + 1);
	else
		return (ft_handle_word(input, i - j - 2, tokens));
}

int	ft_expandvar(char *input, int len, int start, t_shell *shell, t_token **tokens)
{
	char	*var;
	char	*aux;

	var = ft_substr(input, start, len);
	if (!var)
		return(start + 1);
	aux = env_var(shell->envp, var);
	free(var);
	ft_handle_word(aux, 0, tokens);
	return (len + start);
}

int ft_handle_expander(char *input, int i, t_shell *shell, t_token **tokens)
{
	char	*var;
	int		j;

	j = 0;
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