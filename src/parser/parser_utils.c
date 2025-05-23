/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:04:01 by jucoelho          #+#    #+#             */
/*   Updated: 2025/05/23 17:05:03 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_commands(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->argv)
		{
			for (i = 0; cmd->argv[i]; i++)
				free(cmd->argv[i]);
			free(cmd->argv);
		}
		if (cmd->redir_in_file)
			free(cmd->redir_in_file);
		if (cmd->redir_out_file)
			free(cmd->redir_out_file);	
		free(cmd);
		cmd = tmp;
	}
}

void	ft_print_commands(t_command *cmd)
{
	int	i;

	while (cmd)
	{
		printf("Comando:\n");
		if (cmd->argv)
		{
			for (i = 0; cmd->argv[i]; i++)
				printf(" argv[%d]: %s\n", i, cmd->argv[i]);
		}
		if (cmd->redir_in)
			printf(" Redir entrada: %s\n", cmd->redir_in_file);
		if (cmd->redir_out)
			printf(" Redir saída: %s\n", cmd->redir_out_file);
		cmd = cmd->next;
	}
}
