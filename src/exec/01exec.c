/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:21:37 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/19 00:27:59 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_setup_redir_out(t_shell *shell, t_command *cmd)
{
	if (shell->append > 0)
		cmd->fd_out = open(cmd->redir_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (cmd->redir_out)
		cmd->fd_out = open(cmd->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_out < 0)
	{
		perror(cmd->redir_out);
		exit(EXIT_FAILURE);
	}
	cmd->fd_out = ft_dup_close(cmd->fd_out, STDOUT_FILENO);
}

static void	ft_setup_redir_in(t_command *cmd)
{
		cmd->fd_in = open(cmd->redir_in, O_RDONLY);
		if (cmd->fd_in < 0)
		{
			perror(cmd->redir_in);
			exit(EXIT_FAILURE);
		}
		cmd->fd_in = ft_dup_close(cmd->fd_in, STDIN_FILENO);
}

int	ft_setup_redirects_pipe(t_shell *shell,  t_command *cmd, int curr, int last)
{
	printf("\n\n entrou no setup redir");
	if (curr == last)
	{
		if (cmd->redir_in)
		{
			ft_setup_redir_in(cmd);
			(shell->prev_fd) = ft_close_reset(shell->prev_fd);
		}
		else
			shell->prev_fd = ft_dup_close(shell->prev_fd, STDIN_FILENO);
		if (cmd->redir_out)
			ft_setup_redir_out(shell, cmd);
		shell->fd[1] = ft_close_reset(shell->fd[1]);
		shell->fd[0] = ft_close_reset(shell->fd[0]);
	}
	else if (curr == 0)
	{
		if (cmd->redir_in)
			ft_setup_redir_in(cmd);
		shell->fd[0] = ft_close_reset(shell->fd[0]);
		if (cmd->redir_out)
		{
			ft_setup_redir_out(shell, cmd);
			shell->fd[1] = ft_close_reset(shell->fd[1]);
		}
		else
			shell->fd[1] = ft_dup_close(shell->fd[1], STDOUT_FILENO);
	}
	else
	{
		if (cmd->redir_in)
		{
			ft_setup_redir_in(cmd);
			shell->prev_fd = ft_close_reset(shell->prev_fd);
		}	
		else
			shell->prev_fd = ft_dup_close(shell->prev_fd, STDIN_FILENO);
		shell->fd[0] = ft_close_reset(shell->fd[0]);
		if (cmd->redir_out)
		{
			ft_setup_redir_out(shell, cmd);	
			shell->fd[1] = ft_close_reset(shell->fd[1]);
		}
		else
			shell->fd[1] = ft_dup_close(shell->fd[1], STDOUT_FILENO);
	}
	return (shell->status);
}

int	ft_setup_redirects(t_shell *shell, t_command *cmd)
{
	printf("\n\n entrei no redirects\n\n");
	if (cmd->redir_in)
	{
		printf("\n\n entrei no redirects in \n\n");
		ft_setup_redir_in(cmd);
	}
	if (cmd->redir_out)
	{
		printf("\n\n entrei no redirects out \n\n");
		ft_setup_redir_out(shell, cmd);
	}
	return (shell->status);
}
