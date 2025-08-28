/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01exp_squot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 21:17:59 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/28 16:22:14 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_is_squoted(t_command *cmds, char quote)
{
	int		i;

	while (cmds)
	{
		i = 0;
		while (cmds->argv && cmds->argv[i])
		{
			if (ft_strchr(cmds->argv[i], quote))
				cmds->argv[i] = ft_remove_quotes(cmds->argv[i], quote);
			i++;
		}
		if (cmds->redir_in)
			if (ft_strchr(cmds->redir_in, quote))
				cmds->redir_in = ft_remove_quotes(cmds->redir_in, quote);
		if (cmds->redir_out)
			if (ft_strchr(cmds->redir_out, quote))
				cmds->redir_out = ft_remove_quotes(cmds->redir_out, quote);
		cmds = cmds->next;
	}
}
