/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:22:56 by gapachec          #+#    #+#             */
/*   Updated: 2025/08/19 18:19:34 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

/*
 * @brief Handles escaped characters in the input.
 *
 * Advances past the backslash and returns a string containing the escaped character.
 *
 * @param input The full input string.
 * @param i     Pointer to the current index in the string. It is updated internally.
 *
 * @return A newly allocated string containing the escaped character, or NULL on failure.
 */
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

/*
 * @brief Parses and adds operator tokens (pipes and redirections).
 *
 * Identifies whether the current position in the input string matches
 * an operator token like |, >, >>, <, or <<, and adds the corresponding
 * token to the list.
 *
 * @param input  The full input string.
 * @param i      Current index in the input string.
 * @param tokens Pointer to the token list.
 *
 * @return The new index after processing the operator.
 */
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

int	ft_closequoted(char *input, int i)
{
	char	quoted;

	quoted = input[i];
	i++;
	while (input[i] && input[i] != quoted)
	{
		i++;
	}
	if (!input[i])
		return (0);
	return (i);
}

int	ft_handle_word(char *input, int i, t_token **tokens)
{
	int	start;

	start = i;
	while (input[i] && !ft_is_special_char(input[i]))
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			i = ft_closequoted (input, i);
			if (i == 0)
			{
				printf("minishell error: unclosed quote\n");
				ft_free_tokens(*tokens);
				exit(EXIT_FAILURE);
			}
		}
			i++;
	}
	if (i > start)
	{
		ft_add_token(tokens, ft_new_token
			(T_WORD, ft_substr(input, start, i - start)));
	}
	return (i);
}
