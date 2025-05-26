/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:25:12 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/25 23:02:26 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * print_tokens:
 * Imprime a lista de tokens, mostrando o tipo e o valor.
 * Útil para debugar o lexer.
 */
void	ft_print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: [%d] \"%s\"\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
}

/*
 * free_tokens:
 * Libera toda a memória ocupada pela lista de tokens e suas strings.
 * Deve ser chamada após o uso da lista para evitar vazamentos.
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
