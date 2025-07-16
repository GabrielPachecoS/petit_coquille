/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:35:40 by jucoelho          #+#    #+#             */
/*   Updated: 2025/07/16 16:40:06 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_closefd(t_shell *shell)
{
	close(shell->fd[0]);
	close(shell->fd[1]);
	close(shell->fd_in);
	close(shell->fd_out);
}

static void	handle_exec(t_shell *shell, t_command *cmd)
{
	char	**envp;
	char	*fullpath;

	envp = env_to_array(shell->envp);
	fullpath = ft_get_cmdpath(cmd->argv[0], shell->envp);
	if (execve(fullpath, cmd->argv, envp) == -1)
		ft_error_execve(shell);
}

static void	setup_redirects(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

int	ft_handle_pid(t_shell *shell, t_command *cmd, int curr, int last, int prev_fd)
{
	if (curr == 0)
	{
		setup_redirects(STDIN_FILENO, shell->fd[1]);
		close(shell->fd[0]);
	}
	else if (curr < last)
	{
		setup_redirects(prev_fd, shell->fd[1]);
	}
	else
	{
		setup_redirects(prev_fd, STDOUT_FILENO);
	}
	handle_exec(shell, cmd);
	return (1);
}

int	ft_loop_cmdpipe(t_shell *shell, t_command *cmd, int *pid, int n_cmd)
{
	int	i;
	int	prev_fd;

	i = 0;
	prev_fd = STDIN_FILENO;
	while (cmd)
	{
		if (pipe(shell->fd) < 0)
			return (ft_error(1, "pipe failed"));
		pid[i] = fork();
		if (pid[i] < 0)
			return (ft_error(1, "fork failed"));
		if (pid[i] == 0)
			ft_handle_pid(shell, cmd, i, n_cmd - 1, prev_fd);
		close(shell->fd[1]);
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		prev_fd = shell->fd[0];
		cmd = cmd->next;
		i++;
	}
	return (0);
}

int	ft_exec_cmdpipe(t_shell *shell, t_command *cmd, int n_cmd)
{
	int	*pid;
	int	status;
	int	i;

	i = 0;
	pid = malloc(sizeof(int) * (n_cmd + 1));
	if (!pid)
		return (ft_error(1, "malloc failed"));
	status = ft_loop_cmdpipe(shell, cmd, pid, n_cmd);
	ft_closefd(shell);
	while (i < n_cmd)
	{
		if (i == n_cmd - 1)
			waitpid(pid[i], &status, 0);
		else
			waitpid(pid[i], NULL, 0);
		i++;
	}
	free(pid);
	shell->status = status >> 8;
	return (status >> 8);
}
