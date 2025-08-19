/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:35:40 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/19 16:49:38 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_setup_fork(t_shell *shell, t_command *cmds, int *pid, int i)
{
	if (cmds->next != NULL)
		if (pipe(shell->fd) < 0)
			return (ft_error(1, "pipe failed"));
	pid[i] = fork();
	if (pid[i] < 0)
		return (ft_error(1, "fork failed"));
	return (shell->status);
}

int	ft_dup_close(int close_fd, int dup_fd)
{
	dup2(close_fd, dup_fd);
	close(close_fd);
	return (-1);
}

int	ft_close_reset(int close_fd)
{
	close(close_fd);
	return (-1);
}

static void	ft_verifybuiltin(t_shell *shell, t_command *cmds)
{
	if (ft_is_builtin(cmds))
	{
		ft_exec_simplebuiltin(shell, cmds->argv);
		exit(0);
	}
	else
		ft_exec_command(shell, cmds);
}

/*static int	ft_verify_redir_in(t_shell *shell, t_command *cmd)
{
	cmd->fd_in = open(cmd->redir_in, O_RDONLY);
	if (cmd->fd_in < 0)
	{
		perror(cmd->redir_in);
		shell->status = 256;
		return (0);
	}
	return (1);
}*/


int	ft_loop_cmdpipe(t_shell *shell, t_command *cmds, int *pid, int n_cmd)
{
	int	i;

	i = 0;
	while (cmds)
	{
		/*if (cmds->redir_in)
		{
			if ((cmds) && (ft_verify_redir_in(shell, cmds) == 0))
			{
				cmds = cmds->next;
				i++;
				continue ;
			}
		}
		if (cmds)
		{*/
			ft_setup_fork(shell, cmds, pid, i);
			if (pid[i] == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				ft_setup_redirects_pipe(shell, cmds, i, n_cmd - 1);
				ft_verifybuiltin(shell, cmds);
			}
			else
			{
				shell->fd[1] = ft_close_reset(shell->fd[1]);
			}
			if (shell->prev_fd > 0)
				shell->prev_fd = ft_close_reset(shell->prev_fd);
			if (cmds->next != NULL)
				shell->prev_fd = shell->fd[0];
			else
				shell->fd[0] = ft_close_reset(shell->fd[0]);
			cmds = cmds->next;
			i++;
//		}
	}
	if (shell->prev_fd > 0)
		shell->prev_fd = ft_close_reset(shell->prev_fd);
	return (shell->status);
}
