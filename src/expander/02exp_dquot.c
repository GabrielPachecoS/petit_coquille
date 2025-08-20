/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02exp_dquot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 21:24:12 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/19 22:24:42 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

void	ft_is_redirquoted(t_command *cmds, t_shell *shell, char quote)
{
	int	i;

	i = 0;
	if (cmds->redir_in->value)
	{
		if (ft_strchr(cmds->redir_in->value, quote))
		{
			if (ft_strchr(cmds->argv[i], '$'))
				ft_handle_expander(cmds->argv[i], shell);
			else
				cmds->redir_in->value = ft_remove_quotes (cmds->redir_in->value, quote);
		}
	}
	if (cmds->redir_out->value)
	{
		if (ft_strchr(cmds->redir_out->value, quote))
		{
			if (ft_strchr(cmds->argv[i], '$'))
				ft_handle_expander(cmds->argv[i], shell);
			else
				cmds->redir_out->value = ft_remove_quotes(cmds->redir_out->value, quote);
		}
	}
}

void	ft_is_dquoted(t_command *cmds, t_shell *shell, char quote)
{
	int	i;

	while (cmds)
	{
		i = 0;
		while (cmds->argv && cmds->argv[i])
		{
			if (ft_strchr(cmds->argv[i], quote))
			{
				if (ft_strchr(cmds->argv[i], '$'))
					ft_handle_expander(cmds->argv[i], shell);
				else
					cmds->argv[i] = ft_remove_quotes(cmds->argv[i], quote);
			}
			i++;
		}
		ft_is_redirquoted(cmds, shell, quote);
		cmds = cmds->next;
	}
}
