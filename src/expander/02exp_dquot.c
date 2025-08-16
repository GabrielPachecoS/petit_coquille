/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02exp_dquot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 21:24:12 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/15 21:37:08 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

void	ft_is_dquoted(cmds, char quote)
{
	int	i;
	
	while(cmds)
	{
		i = 0;
		while (cmds->argv && cmds->argv[i])
		{
			if(ft_strchr(cmds->argv[i], quote))
			{
				if (ft_strchr(cmds->argv[i], '$'))
					ft_handle_expander(cmds, i)
				else
					cmds->argv = ft_remove_quotes(cmds->argv, int c);
			}
			i++;
		}
		ft_is_redirquoted(cmds, quote);	
		cmds = cmds->next
	}
}
ft_is_redirquoted(cmds, quote)
{
	if(cmds->redir_in)
	{
		if(ft_strchr(cmds->redir_in, quote))
		{
			if (ft_strchr(cmds->argv[i], '$'))
				ft_handle_expander(cmds, i)
			else
				cmds->redir_in= ft_remove_quotes(cmds->redir_in, int c);
		}
	}
	if(cmds->redir_out)
	{
		if(ft_strchr(cmds->redir_out, quote))
		{
			if (ft_strchr(cmds->argv[i], '$'))
				ft_handle_expander(cmds, i)
			else
				cmds->redir_out= ft_remove_quotes(cmds->redir_out, int c);	
		}
	}
}


