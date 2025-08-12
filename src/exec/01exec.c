/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:21:37 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/11 21:21:59 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_setup_redir_out(t_shell *shell)
{
	if (shell->append > 0)
		shell->prev_fd = open(shell->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (shell->outfile)
		shell->prev_fd = open(shell->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (shell->prev_fd < 0)
	{
		perror(shell->outfile);
		exit(EXIT_FAILURE);
	}
	ft_dup_close(shell->prev_fd, STDOUT_FILENO);
}

static void	ft_setup_redir_in(t_shell *shell)
{
	if (shell->infile)
	{	
		shell->prev_fd = open(shell->infile, O_RDONLY);
		if (shell->prev_fd < 0)
		{
			perror(shell->infile);
			exit(EXIT_FAILURE);
		}
		ft_dup_close(shell->prev_fd, STDIN_FILENO);
	}
}

int	ft_setup_redirects_pipe(t_shell *shell, int curr, int last)
{
	if (curr == last)
	{
		ft_dup_close(shell->prev_fd, STDIN_FILENO);
		if (shell->outfile)
			ft_setup_redir_out(shell);	
		ft_close_reset(shell->fd[0]);
		ft_close_reset(shell->fd[1]);
	}
	else if (curr == 0)
	{
		if (shell->infile)
			ft_setup_redir_in(shell);
		ft_close_reset(shell->fd[0]);
		ft_dup_close(shell->fd[1], STDOUT_FILENO);
	}
	else
	{
		ft_dup_close(shell->prev_fd, STDIN_FILENO);
		ft_dup_close(shell->fd[1], STDOUT_FILENO);
		ft_close_reset(shell->fd[0]);
	}
	return (shell->status);
}

int	ft_setup_redirects(t_shell *shell)
{
	if (shell->infile)
	{
		ft_setup_redir_in(shell);
	}
	if (shell->outfile)
	{
		ft_setup_redir_out(shell);
	}
	return (shell->status);
}
