/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02parser_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:52:06 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/28 16:57:16 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

/**
 * @brief Frees all commands in the linked list, including their argv arrays
 *        and redirection strings.
 *
 * @param cmd Pointer to the head of the command list.
 */
void	ft_free_commands(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	while (cmd)
	{
		i = 0;
		tmp = cmd->next;
		if (cmd->argv)
		{
			while (cmd->argv[i])
				free(cmd->argv[i++]);
			free(cmd->argv);
		}
		if (cmd->redir_in)
			free(cmd->redir_in);
		if (cmd->redir_out)
			free(cmd->redir_out);
		free(cmd);
		cmd = tmp;
	}
}
