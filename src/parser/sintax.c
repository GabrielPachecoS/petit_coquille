/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:52:06 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/26 20:46:22 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_verifysintax(t_token *tokens)
{
	t_token	*tok;

	tok = tokens;
	if (tok->type == T_PIPE)
		return (printf("Syntax error near unexpected token `|'\n"), 1);
	while (tok)
	{
		if (tok->type == T_PIPE)
		{
			if (!tok->next || tok->next->type == T_PIPE)
				return (printf("Syntax error near unexpected token `|'\n"), 1);
		}
		else if (tok->type == T_REDIR_IN || tok->type == T_REDIR_OUT
			|| tok->type == T_HEREDOC || tok->type == T_REDIR_APPEND)
		{
			if (!tok->next || tok->next->type != T_WORD)
				return (
					printf("syntax error near unexpected token `newline'\n"), 1);
		}
		tok = tok->next;
	}
	return (0);
}
