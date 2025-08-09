/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:21:37 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/08 18:14:27 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_setup_redir_out(t_shell *shell)
{
	if (shell->append > 0)
		shell->fd_out = open(shell->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (shell->fd_out > 0)
		shell->fd_out = open(shell->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);	
	if (shell->fd_out < 0)
	{
			close(shell->fd[1]);
			perror(shell->outfile);
			exit(EXIT_FAILURE);
	}
	ft_dup_close(shell->fd_out, STDOUT_FILENO);
}

static void	ft_setup_redir_in(t_shell *shell)
{
	if (shell->infile)
	{	
		shell->fd_in = open(shell->infile, O_RDONLY);
		if (shell->fd_in < 0)
		{
			perror(shell->infile);
			exit(EXIT_FAILURE);
		}
	}
	ft_dup_close(shell->fd[1], STDOUT_FILENO);
}

int	ft_setup_redirects_pipe(t_shell *shell, int curr, int last, int prev_fd)
{
	//printf("redirects: curr %d\n", curr);
	if (curr == last)
	{
		//printf("redirects curr=last: curr %d\n", curr);
		if (shell->outfile)
			ft_setup_redir_out(shell);
		else	
			ft_dup_close(prev_fd, STDIN_FILENO);
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
	}
	else if (curr == 0)
	{
		if (shell->infile)
			ft_setup_redir_in(shell);
		else
		{
			ft_dup_close(shell->fd[1], STDOUT_FILENO);
			shell->fd_in = -1;
		}
	}
	else if (shell->fd_in <= 0)
	{
		ft_dup_close(prev_fd, STDIN_FILENO);
		ft_dup_close(shell->fd[1], STDOUT_FILENO);
	}
	//printf("redirects return: curr %d\n", curr);
	return (shell->status);
}

int	ft_setup_redirects(t_shell *shell)
{
	if (shell->infile > 0)
	{
		ft_setup_redir_in(shell);
	}
	if (shell->outfile > 0)
	{
		ft_setup_redir_out(shell);
	}
	return (shell->status);
}