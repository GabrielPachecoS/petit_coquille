/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:25:12 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/25 19:02:30 by jucoelho         ###   ########.fr       */
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
