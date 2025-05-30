/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:22:56 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/30 13:40:38 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_token(char *input, int i, t_token **tokens)
{
	if (input[i] == '|' || input[i] == '>' || input[i] == '<')
	{
		if (input[i] == '>' && input[i + 1] == '>')
			return (ft_add_simple_token(tokens, T_REDIR_APPEND, input, i, 2));
		if (input[i] == '<' && input[i + 1] == '<')
			return (ft_add_simple_token(tokens, T_HEREDOC, input, i, 2));
		if (input[i] == '>')
			return (ft_add_simple_token(tokens, T_REDIR_OUT, input, i, 1));
		if (input[i] == '<')
			return (ft_add_simple_token(tokens, T_REDIR_IN, input, i, 1));
		if (input[i] == '|')
			return (ft_add_simple_token(tokens, T_PIPE, input, i, 1));
	}
	return (i);
}

int	ft_handle_word(char *input, int i, t_token **tokens)
{
	int	start;

	start = i;
	while (input[i] && !ft_is_special_char(input[i]))
		i++;
	if (i > start)
	{
		ft_add_token(tokens,
			ft_new_token(T_WORD, ft_substr(input, start, i - start)));
	}
	return (i);
}


char	*ft_handle_escaped_char(const char *input, int *i)
{
	char	*res;

	(*i)++;
	if (!input[*i])
		return (ft_strdup(""));
	res = malloc(2);
	if (!res)
		return (NULL);
	res[0] = input[*i];
	res[1] = '\0';
	(*i)++;
	return (res);
}

int	ft_handle_quoted(char *input, int i, t_token **tokens, char quote)
{
	int	start;
	int	len;

	start = ++i;
	while (input[i] && input[i] != quote)
	{
		if (input[i] == '\\' && input[i + 1]
			&& (input[i + 1] == '\\' || input[i + 1] == '"' || input[i + 1] == '$'))
			i++;
		i++;
	}
	if (input[i] == quote)
	{
		len = i - start;
		ft_add_token(tokens, ft_new_token(T_WORD, ft_substr(input, start, len)));
		return (i + 1);
	}
	return (start - 1);
}
