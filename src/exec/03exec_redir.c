/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03exec_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 01:56:38 by codespace         #+#    #+#             */
/*   Updated: 2025/08/19 01:57:47 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_prepare_redir_in(t_command *cmd)
{
	int	fd;

	if (!cmd->redir_in)
		return (0);
	fd = open(cmd->redir_in, O_RDONLY);
	if (fd < 0)
	{
		perror(cmd->redir_in);
		return (-1);
	}
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	cmd->fd_in = fd;
	return (0);
}

static int	ft_prepare_redir_out(t_shell *shell, t_command *cmd)
{
	int	fd;
	int	flags;

	if (!cmd->redir_out)
		return (0);
	flags = O_WRONLY | O_CREAT;
	if (shell->append > 0)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(cmd->redir_out, flags, 0644);
	if (fd < 0)
	{
		perror(cmd->redir_out);
		return (-1);
	}
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	cmd->fd_out = fd;
	return (0);
}

int	ft_prepare_redirections(t_shell *shell, t_command *cmd)
{
	if (ft_prepare_redir_in(cmd) < 0)
		return (-1);
	if (ft_prepare_redir_out(shell, cmd) < 0)
		return (-1);
	return (0);
}
