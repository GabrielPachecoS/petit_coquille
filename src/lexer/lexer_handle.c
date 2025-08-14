/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:22:56 by gapachec          #+#    #+#             */
/*   Updated: 2025/08/14 20:09:24 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

/**
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
static char	*extract_word(char *input, int *i, char *quote_type)
{
	int		start;

	*quote_type = 0;
	start = *i;
	while (input[*i] && !ft_is_special_char(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			if (!skip_quoted_word(input, i, quote_type))
				return (NULL);
		}
		else
			(*i)++;
	}
	return (ft_substr(input, start, *i - start));
}

static int	skip_quoted_word(char *input, int *i, char *quote_type)
{
	char	q;

	q = input[*i];
	*quote_type = q;
	(*i)++;
	while (input[*i] && input[*i] != q)
		(*i)++;
	if (input[*i] == '\0')
	{
		printf("minishell error: unclosed %c quote\n", q);
		return (0);
	}
	(*i)++;
	return (i);
}

int	ft_handle_word(char *input, int i, t_token **tokens)
{
	char	*word;
	char	quote_type;
	
	word = extract_word(input, i, &quote_type);
	if (!word)
		return (0);
	ft_add_token(tokens,
			ft_new_token(T_WORD, ft_substr(input, start, i - start)));;
	free(word);
	return (i);
}


/**
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

/**
 * @brief Parses a quoted string and adds it as a T_WORD token.
 *
 * Extracts the content inside matching single or double quotes, handling
 * escaped characters inside double quotes. If the closing quote is found,
 * a new T_WORD token is added to the token list.
 *
 * @param input  The full input string.
 * @param i      Index of the opening quote.
 * @param tokens Pointer to the token list.
 * @param quote  The quote character (either ' or ").
 *
 * @return The new index after the closing quote, or the original position on error.
 */
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
