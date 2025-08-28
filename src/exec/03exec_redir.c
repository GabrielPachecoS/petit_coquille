/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03exec_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:15:23 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/28 15:19:32 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setup_last(t_shell *shell, t_command *cmd)
{
	if (cmd->redir_in)
	{
		ft_setup_redir_in(cmd);
		ft_close_reset(&shell->prev_fd);
	}
	else
		shell->prev_fd = ft_dup_close(shell->prev_fd, STDIN_FILENO);
	if (cmd->redir_out)
		ft_setup_redir_out(shell, cmd);
	ft_close_reset(&shell->fd[1]);
	ft_close_reset(&shell->fd[0]);
}

void	ft_setup_first(t_shell *shell, t_command *cmd)
{
	if (cmd->redir_in)
		ft_setup_redir_in(cmd);
	ft_close_reset(&shell->fd[0]);
	if (cmd->redir_out)
	{
		ft_setup_redir_out(shell, cmd);
		ft_close_reset(&shell->fd[1]);
	}
	else
		shell->fd[1] = ft_dup_close(shell->fd[1], STDOUT_FILENO);
}

void	ft_setup_middle(t_shell *shell, t_command *cmd)
{
	if (cmd->redir_in)
	{
		ft_setup_redir_in(cmd);
		ft_close_reset(&shell->prev_fd);
	}
	else
		shell->prev_fd = ft_dup_close(shell->prev_fd, STDIN_FILENO);
	ft_close_reset(&shell->fd[0]);
	if (cmd->redir_out)
	{
		ft_setup_redir_out(shell, cmd);
		ft_close_reset(&shell->fd[1]);
	}
	else
	{
		shell->fd[1] = ft_dup_close(shell->fd[1], STDOUT_FILENO);
	}
}
