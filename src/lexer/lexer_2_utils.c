/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:28:57 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/30 13:29:29 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add_simple_token(t_token **tokens, t_token_type type,
			char *input, int i, int size)
{
	ft_add_token(tokens, ft_new_token(type, ft_substr(input, i, size)));
	return (i + size);
}

int	ft_is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	ft_is_special_char(char c)
{
	return (c == ' ' || c == '\\' || c == '"' || c == '\''
		|| c == '|' || c == '<' || c == '>');
}
