/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:21:37 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/19 22:25:34 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setup_redir_out(t_shell *shell, t_command *cmd)
{
	if (shell->append > 0)
		cmd->fd_out = open(cmd->redir_out->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (cmd->redir_out)
		cmd->fd_out = open(cmd->redir_out->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_out < 0)
	{
		perror(cmd->redir_out->value);
		exit(EXIT_FAILURE);
	}
	cmd->fd_out = ft_dup_close(cmd->fd_out, STDOUT_FILENO);
}

void	ft_setup_redir_in(t_command *cmd)
{
	cmd->fd_in = open(cmd->redir_in->value, O_RDONLY);
	if (cmd->fd_in < 0)
	{
		perror(cmd->redir_in->value);
		exit(EXIT_FAILURE);
	}
	else
		cmd->fd_in = ft_dup_close(cmd->fd_in, STDIN_FILENO);
}

int	ft_setup_redirects_pipe(t_shell *shell, t_command *cmd, int curr, int last)
{
	if (curr == last)
		ft_setup_last(shell, cmd);
	else if (curr == 0)
		ft_setup_middle(shell, cmd);
	else
	{
		ft_setup_first(shell, cmd);
	}
	return (shell->status);
}

int	ft_setup_redirects(t_shell *shell, t_command *cmd)
{
	if (cmd->redir_in)
	{
		while (cmd->redir_in)
		{
			ft_setup_redir_in(cmd);
			cmd->redir_in = cmd->redir_in->next;
		}
	}
	if (cmd->redir_out)
	{
		while (cmd->redir_out)
		{
			ft_setup_redir_out(shell, cmd);
			cmd->redir_out = cmd->redir_out->next;
		}
	}
	return (shell->status);
}
