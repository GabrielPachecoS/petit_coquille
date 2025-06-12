/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:05:02 by jucoelho          #+#    #+#             */
/*   Updated: 2025/06/11 21:28:59 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_pipe(int **fd, int i)
{
	close(fd[i][0]);
	close(fd[i][1]);
}


int	ft_handle_pid(t_shell *shell, t_command *cmd, int i)
{
	
	if (cmd->infile)
	{
		ft_handle_infile(shell, cmd, i);
	}
	else if (cmd->outfile)
	{
		ft_handle_outfile(shell, cmd, i);
	}
	else
	{
		ft_handle_cmd(shell, cmd, i);
	}
	return (1);
}
int	ft_handle_infile(t_shell *shell, t_command *cmd, int i)
{
	char	*fullpath;
	
	cmd->fd_in = open(cmd->infile, O_RDONLY);
	if (cmd->fd_in < 0)
	{
		perror("fd_in");
		exit(EXIT_FAILURE);
	}
	dup2(cmd->fd_in, STDIN_FILENO);
	close(cmd->fd_in);
	if (cmd->next != NULL)
	{
		dup2(shell->fd[i][1], STDOUT_FILENO);
		close(shell->fd[i][0]);
		close(shell->fd[i][1]);
	}
	fullpath = ft_get_cmdpath(cmd->argv[0], shell->envp);
	if (execve(fullpath, cmd->argv, shell->envp) == -1)
		ft_error_execve(cmd);
	return (1);
}
int	ft_handle_outfile(t_shell *shell, t_command *cmd, int i)
{
	char	*fullpath;
	
	if (i > 0)
	{
		dup2(shell->fd[i - 1][0], STDIN_FILENO);
		close(shell->fd[i - 1][0]);
		close(shell->fd[i - 1][1]);
	}
	cmd->fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_out < 0)
	{
		ft_error(1, "fd_out");
		exit(EXIT_FAILURE);
	}
	dup2(cmd->fd_out, STDOUT_FILENO);
	close(cmd->fd_out);
	fullpath = ft_get_cmdpath(cmd->argv[0], shell->envp);
	if (execve(fullpath, cmd->argv, shell->envp) == -1)
		ft_error_execve(cmd);
	return (1);
}

int	ft_handle_cmd(t_shell *shell, t_command *cmd, int i)
{
	char	*fullpath;
	
	if (i > 0)
	{
		dup2(shell->fd[i - 1][0], STDIN_FILENO);
		close(shell->fd[i - 1][0]);
		close(shell->fd[i - 1][1]);
	}
	if (cmd->next != NULL) // se ainda tem comando depois
	{
		dup2(shell->fd[i][1], STDOUT_FILENO);
		close(shell->fd[i][0]);
		close(shell->fd[i][1]);
	}
	fullpath = ft_get_cmdpath(cmd->argv[0], shell->envp);
	if (execve(fullpath, cmd->argv, shell->envp) == -1)
		ft_error_execve(cmd);
	return (1);
}

int	ft_exec_cmdpipe(t_shell *shell, t_command *cmd, int n_cmd)
{
	pid_t		*pid;
	int			status;
	int			i;
	
	i = 0;
	pid = malloc(sizeof(pid_t) * n_cmd);
	if (!pid)
		return (ft_error(1, "malloc failed"));
	while (cmd != NULL)
	{
		shell->fd[i] = malloc(sizeof(int) * 2);
		if (!shell->fd[i])
			return (ft_error(1, "malloc failed"));
		pid[i] = ft_fork(shell, cmd, i);
		cmd = cmd->next;
		i++;
	}
	i = 0;
	while (i < n_cmd)
	{
		if (i == n_cmd - 1)
			waitpid(pid[i], &status, 0);
		else
			waitpid(pid[i], NULL, 0);
		i++;
	}
	free(pid);
	status = status >> 8;
	return (status);
}

pid_t	ft_fork(t_shell *shell, t_command *cmd, int i)
{
	t_command	*current;
	pid_t		pid;
	
	pid = -1;
	current = cmd;
	if (pipe(shell->fd[i]) < 0)
			return (ft_error(1, "pipe failed"));
	pid = fork();
	if (pid < 0)
		return (ft_error(1, "fork failed"));
	if (pid == 0)
	{
		ft_handle_pid(shell, current, i);
	}
	if (pid > 0 && cmd->next != NULL)
		ft_close_pipe(shell->fd, i);
	return(pid);
}



