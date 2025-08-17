/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00expander.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:49:27 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/16 21:25:14 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

t_command	*ft_expander(t_shell *shell, t_command *cmds, t_token **tokens)
{
	t_command *head;
	int	i;

	i = 0;
	head = cmds;
	ft_is_squoted(cmds, '\'');
	cmds = head;
	ft_is_dquoted(cmds, shell, tokens, '"');
	cmds = head;
	while (cmds)
	{
		while(cmds->argv[i])
		{
			printf("\n1)cmds = %s\n", cmds->argv[i]);
			cmds->argv[i] = ft_handle_expander(cmds->argv[i], i, shell, tokens);
			i++;
		}
		cmds = cmds->next;
	}
	return(head);
}
