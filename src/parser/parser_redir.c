/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 23:26:23 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/20 00:41:34 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	ft_count_redir(t_token **tok, int count)
{
	while (*tok)
	{
		if ((*tok)->type == T_REDIR_IN)	
			(count++);
		*tok = (*tok)->next;
	}
	return(count);
}

t_redirect	*ft_start_redir(int type, char *value)
{
	t_redirect	*redir;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->value = value;
	redir->next = NULL;
	return (redir);
}
