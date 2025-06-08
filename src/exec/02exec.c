/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:57:17 by jucoelho          #+#    #+#             */
/*   Updated: 2025/06/07 20:09:02 by jucoelho         ###   ########.fr       */
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

int	ft_handle_pid(t_shell *shell, t_command *cmd, int curr_cmd, int last_cmd)
{
	char	*fullpath;
	
	if (curr_cmd == 0)
	{
		dup2(shell->fd_in, STDIN_FILENO);
		dup2(shell->fd[1], STDOUT_FILENO);
		close(shell->fd[0]);
		close(shell->fd[1]);
		fullpath = ft_get_cmdpath(cmd->argv, shell->envp);
		if (execve(fullpath, cmd, shell->envp) == -1)
			ft_error_execve(shell);
	}
	else if (curr_cmd < last_cmd)
	{
		ft_handle_middlecmd(shell, cmd);
	}
	else if (curr_cmd == last_cmd)
	{
		ft_handle_lastcmd(shell, cmd);
	}
	return (1);
}

int	ft_handle_middlecmd(t_shell *shell, t_command *cmd)
{
	char	*fullpath;
	
	dup2(shell->fd[0], STDIN_FILENO);
	dup2(shell->fd[1], STDOUT_FILENO);
	close(shell->fd[0]);
	close(shell->fd[1]);
	fullpath = ft_get_cmdpath(cmd->argv, shell->envp);
	if (execve(fullpath, cmd, shell->envp) == -1)
		ft_error_execve(shell);
	return (1);
}
int	ft_handle_lastcmd(t_shell *shell, t_command *cmd)
{
	char	*fullpath;
	
	dup2(shell->fd[0], STDIN_FILENO);
	dup2(shell->fd_out, STDOUT_FILENO);
	close(shell->fd[0]);
	close(shell->fd[1]);
	fullpath = ft_get_cmdpath(cmd->argv, shell->envp);
	if (execve(fullpath, cmd, shell->envp) == -1)
		ft_error_execve(shell);
	return (1);
}

int	ft_exec_cmdpipe(t_shell *shell, t_command *cmd, int n_cmd)
{
	int		*pid;
	int		i;
	int		status;

	i = 0;
	while (cmd)
	{
		if (pipe(shell->fd) < 0)
			return (ft_error(1, "pipe failed"));
		pid[i] = fork();
		if (pid[i] < 0)
			return (ft_error(1, "fork failed"));
		if (pid[i] == 0)
			ft_handle_pid(shell, cmd, i++, n_cmd);
		cmd = cmd->next;
	}
	ft_closefd(shell);
	while (i > 0)
	{
		waitpid(pid[i], NULL, 0);
		i--;
	}
	waitpid(pid[n_cmd], &status, 0);
	status = status >> 8;
	return (status);
}
