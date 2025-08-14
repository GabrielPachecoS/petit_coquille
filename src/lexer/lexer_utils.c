/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:28:57 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/30 13:29:29 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

/**
 * @brief Checks if a character is a shell operator.
 *
 * Operators include '<', '>' and '|'.
 *
 * @param c Character to check.
 *
 * @return 1 if the character is an operator, 0 otherwise.
 */
int	ft_is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

/**
 * @brief Checks if a character is a special shell character.
 *
 * Special characters include space, backslash, quotes, pipes, and redirections.
 *
 * @param c Character to check.
 *
 * @return 1 if the character is special, 0 otherwise.
 */
int	ft_is_special_char(char c)
{
	return (c == ' ' || c == '|' || c == '<' || c == '>');
}
