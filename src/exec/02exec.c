/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:35:40 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/05 20:39:55 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_setup_fork(t_shell *shell, int *pid, int i)
{
	if (pipe(shell->fd) < 0)
		return (ft_error(1, "pipe failed"));
	pid[i] = fork();
	if (pid[i] < 0)
		return (ft_error(1, "fork failed"));
	return (shell->status);
}

void	ft_close_fd(t_shell *shell)
{
	close(shell->fd[0]);
	close(shell->fd[1]);
	close(shell->fd_in);
	close(shell->fd_out);
}

void	ft_dup_close(int close_fd, int dup_fd)
{
	dup2(close_fd, dup_fd);
	close(close_fd);
}

int	ft_loop_cmdpipe(t_shell *shell, t_command *cmds, int *pid, int n_cmd)
{
	int	i;
	int	prev_fd;

	i = 0;
	prev_fd = STDIN_FILENO;
	while (cmds)
	{
		ft_setup_fork(shell, pid, i);
		if (pid[i] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			ft_setup_redirects_pipe(shell, i, n_cmd - 1, prev_fd);
			if (ft_is_builtin(cmds))
			{
				ft_exec_simplebuiltin(shell, cmds->argv);
				exit(0);
			}
			else
				ft_exec_command(shell, cmds);
		}
		close(shell->fd[1]);
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		prev_fd = shell->fd[0];
		cmds = cmds->next;
		i++;
	}
	close(prev_fd);
	return (shell->status);
}
