/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:25:12 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/30 13:29:50 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

/**
 * @brief Frees a linked list of tokens.
 *
 * Iterates through the token list, freeing each token's value and the token itself.
 *
 * @param tokens Pointer to the first token in the list.
 */
void	ft_free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}
/**
 * @brief Creates a new token node.
 *
 * Allocates and initializes a new token with the given type and value.
 *
 * @param type  The type of the token (e.g., word, operator).
 * @param value The string value of the token.
 *
 * @return Pointer to the newly created token, or NULL on allocation failure.
 */
t_token	*ft_new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}
/**
 * @brief Creates a new token node.
 *
 * Allocates and initializes a new token with the given type and value.
 *
 * @param type  The type of the token (e.g., word, operator).
 * @param value The string value of the token.
 *
 * @return Pointer to the newly created token, or NULL on allocation failure.
 */
void	ft_add_token(t_token **list, t_token *new)
{
	t_token	*cur;

	if (!*list)
	{
		*list = new;
		return ;
	}
	cur = *list;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}
/**
 * @brief Creates and appends a simple token from a substring.
 *
 * Extracts a substring from the input and adds it as a new token
 * of the given type to the token list.
 *
 * @param tokens Pointer to the token list.
 * @param type   Type of the token to be added.
 * @param input  The full input string.
 * @param i      Starting index of the substring.
 * @param size   Length of the substring.
 *
 * @return The new position in the input string after the added token.
 */
int	ft_add_simple_token(t_token **tokens, t_token_type type,
			char *input, int i, int size)
{
	ft_add_token(tokens, ft_new_token(type, ft_substr(input, i, size)));
	return (i + size);
}
