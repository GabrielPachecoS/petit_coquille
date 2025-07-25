/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:21:37 by jucoelho          #+#    #+#             */
/*   Updated: 2025/07/24 17:38:04 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_setup_redir_out(t_shell *shell)
{
	if (shell->append > 0)
		shell->fd_out = open(shell->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (shell->fd_out > 0)
		shell->fd_out = open(shell->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);	
	if (shell->fd_out < 0)
	{
			close(shell->fd[1]);
			//printf("entrou ft_setup redir_out\n");
			perror(shell->outfile);
			exit(EXIT_FAILURE);
	}
	ft_dup_close(shell->fd_out, STDOUT_FILENO);
	return(1);
}

static int	ft_setup_redir_in(t_shell *shell)
{
	if (shell->infile)
	{	
		shell->fd_in = open(shell->infile, O_RDONLY);
		if (shell->fd_in < 0)
		{
			//close (shell->fd[0]);
			perror(shell->infile);
			exit(EXIT_FAILURE);
		}
	}
	ft_dup_close(shell->fd_in, STDIN_FILENO);
	return(1);
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
	return (1);
}
int	ft_setup_redirects_pipe(t_shell *shell, int curr, int last, int prev_fd)
{
	if (curr == last)
	{
		if (shell->outfile)
			ft_setup_redir_out(shell);
		else
			ft_dup_close(prev_fd, STDIN_FILENO);
	}
	else if (curr == 0 && shell->infile)
	{
		ft_setup_redir_in(shell);
		ft_dup_close(shell->fd[1], STDOUT_FILENO);
		shell->fd_in = -1;
	}
	else if (shell->fd_in <= 0)
	{
		ft_dup_close(prev_fd, STDIN_FILENO);
		ft_dup_close(shell->fd[1], STDOUT_FILENO);
	}
	return (1);
}