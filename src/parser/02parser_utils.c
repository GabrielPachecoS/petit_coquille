/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02parser_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:01:20 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/28 17:02:03 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handles pipe token by creating a new command linked to the current one.
 *
 * Sets the next pointer of the current command to a newly allocated command,
 * then updates the current pointer to this new command.
 *
 * @param cmd Double pointer to the current command; will be updated.
 *
 * @return 1 if successful, 0 if memory allocation failed.
 */
int	ft_parser_pipe(t_command **cmd)
{
	(*cmd)->next = ft_new_command();
	if (!(*cmd)->next)
		return (0);
	*cmd = (*cmd)->next;
	return (1);
}

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
