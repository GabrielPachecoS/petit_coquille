/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:24:58 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/28 12:16:10 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_quoted(char *input, int i, t_token **tokens, char quote)
{
	int	start;
	int	len;

	start = ++i;
	while (input[i] && input[i] != quote)
	{
		if ((input[i] == '\\') && (input[i + 1]))
			i += 2;
		else
			i++;
	}
	if (input[i] == quote)
	{
		len = i - start;
		ft_add_token(tokens, ft_new_token(T_WORD,
				ft_substr(input, start, len)));
		return (i + 1);
	}
	return (start - 1);
}

int	ft_handle_token(char *input, int i, t_token **tokens)
{
	if (input[i] == '|')
		return (ft_add_token(tokens, ft_new_token(T_PIPE,
					ft_substr(input, i, 1))), i + 1);
	if (input[i] == '>' && input[i + 1] == '>')
		return (ft_add_token(tokens, ft_new_token(T_REDIR_APPEND,
					ft_substr(input, i, 2))), i + 2);
	if (input[i] == '<' && input[i + 1] == '<')
		return (ft_add_token(tokens, ft_new_token(T_HEREDOC,
					ft_substr(input, i, 2))), i + 2);
	if (input[i] == '>')
		return (ft_add_token(tokens, ft_new_token(T_REDIR_OUT,
					ft_substr(input, i, 1))), i + 1);
	if (input[i] == '<')
		return (ft_add_token(tokens, ft_new_token(T_REDIR_IN,
					ft_substr(input, i, 1))), i + 1);
	return (i);
}

static int	handle_word(char *input, int i, t_token **tokens)
{
	int	start;
	int	len;

	start = i;
	while (input[i] && input[i] != ' ' && input[i] != '\\'
		&& input[i] != '"' && input[i] != '\''
		&& input[i] != '|' && input[i] != '<' && input[i] != '>')
		i++;
	len = i - start;
	if (len > 0)
		ft_add_token(tokens, ft_new_token(T_WORD,
				ft_substr(input, start, len)));
	return (i);
}

t_token	*ft_lexer(char *input)
{
	int		i;
	t_token	*tokens;

	i = 0;
	tokens = NULL;
	while (input[i])
	{
		if (input[i] == ' ')
			i++;
		else if (input[i] == '\\' && input[i + 1])
		{
			i++;
			ft_add_token(&tokens, ft_new_token(T_WORD,
					ft_substr(input, i, 1)));
			i++;
		}
		else if (input[i] == '"' || input[i] == '\'')
			i = handle_quoted(input, i, &tokens, input[i]);
		else if (input[i] == '<' || input[i] == '>' || input[i] == '|')
			i = ft_handle_token(input, i, &tokens);
		else
			i = handle_word(input, i, &tokens);
	}
	return (tokens);
}
