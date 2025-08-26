/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:52:06 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/26 18:18:53 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_verifysintax(t_token *tokens)
{
	if (tokens->type != T_WORD)
	{
		if (tokens->type == T_PIPE)
			printf("syntax error near unexpected token `|'\n");
		else
			printf("syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}