/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:05:02 by jucoelho          #+#    #+#             */
/*   Updated: 2025/06/09 20:09:01 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_closefd(t_command *cmd)
{
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	close(cmd->fd_in);
	close(cmd->fd_out);
}

int	ft_handle_pid(t_shell *shell, t_command *cmd)
{	
	if (cmd->infile)
	{
		ft_handle_infile(shell, cmd);
	}
	else if (cmd->outfile)
	{
		ft_handle_outfile(shell, cmd);
	}
	else
	{
		ft_handle_cmd(shell, cmd);
	}
	return (1);
}
int	ft_handle_infile(t_shell *shell, t_command *cmd)
{
	char	*fullpath;

	printf("handle infile Executando: %s\n", cmd->argv[0]);
	cmd->fd_in = open(cmd->infile, O_RDONLY);
	if (cmd->fd_in < 0)
	{
		perror("fd_in");
	}
	printf("handle infile open");
	dup2(cmd->fd_in, STDIN_FILENO);
	dup2(cmd->fd[1], STDOUT_FILENO);
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	fullpath = ft_get_cmdpath(cmd->argv[0], shell->envp);
	printf("handle infile fullpath : %s\n", fullpath );
	if (execve(fullpath, cmd->argv, shell->envp) == -1)
		ft_error_execve(cmd);
	return (1);
}
int	ft_handle_outfile(t_shell *shell, t_command *cmd)
{
	char	*fullpath;
	
	printf("handle outfile Executando: %s\n", cmd->argv[0]);
	cmd->fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_out < 0)
	{
		ft_error(1, "fd_out");
	}
	dup2(cmd->fd[0], STDIN_FILENO);
	dup2(cmd->fd_out, STDOUT_FILENO);
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	fullpath = ft_get_cmdpath(cmd->argv[0], shell->envp);
	if (execve(fullpath, cmd->argv, shell->envp) == -1)
		ft_error_execve(cmd);
	return (1);
}

int	ft_handle_cmd(t_shell *shell, t_command *cmd)
{
	char	*fullpath;
	
	printf("handle cmd Executando: %s fd[0]: %d\n", cmd->argv[0], cmd->fd[0]);
	dup2(cmd->fd[0], STDIN_FILENO);
	dup2(cmd->fd[1], STDOUT_FILENO);
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	fullpath = ft_get_cmdpath(cmd->argv[0], shell->envp);
	if (execve(fullpath, cmd->argv, shell->envp) == -1)
		ft_error_execve(cmd);
	return (1);
}

int	ft_exec_cmdpipe(t_shell *shell, t_command *cmd, int n_cmd)
{
	int		*pid;
	int		i;
	int		status;
	t_command	*current;
	int prev_pipe_fd = -1;

	current = cmd;
	i = 0;
	pid = malloc(sizeof(int) * n_cmd);
	if (!pid)
		return (ft_error(1, "malloc failed"));
	while (current->argv)
	{
		if (pipe(current->fd) < 0)
			return (ft_error(1, "pipe failed"));
		if (prev_pipe_fd != -1)
			current->fd[0] = prev_pipe_fd; // entrada = saída anterior
		pid[i] = fork();
		if (pid[i] < 0)
			return (ft_error(1, "fork failed"));
		if (pid[i] == 0)
		{
			printf("VAI ENTRAR ft_handle pid prev_pipe: %d, current ->argv[i] = %s, fd[0]: %d\n", prev_pipe_fd, current->argv, current ->fd[0]);
			prev_pipe_fd = current ->fd[0]; // guarda entrada para o próximo
			ft_handle_pid(shell, current);
		}
		if (pid[i] > 0)
			ft_closefd(current);
		i++;
		current = current->next;
	}
	while (i > 0)
	{
		waitpid(pid[i - 1], NULL, 0);
		i--;
	}
	waitpid(pid[n_cmd - 1], &status, 0);
	status = status >> 8;
	return (status);
	return (1);
}
