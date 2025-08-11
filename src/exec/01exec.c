/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:21:37 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/10 18:33:42 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_setup_redir_out(t_shell *shell)
{
	if (shell->append > 0)
		shell->fd_out = open(shell->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (shell->fd_out > 0)
	{
		//printf("is setup_out redir out\n\n");
		shell->fd_out = open(shell->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (shell->fd_out < 0)
	{
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
			printf("perror redir in shell status= %d\n\n\n", shell->status);
			perror(shell->infile);
			exit(EXIT_FAILURE);
			//printf("depois exit in shell status= %d\n\n\n", shell->status);
		}
		ft_dup_close(shell->fd_in, STDIN_FILENO);
	}
}

int	ft_setup_redirects_pipe(t_shell *shell, int curr, int last, int prev_fd)
{
	//printf("redirects: curr %d last %d, prev_fd %d\n", curr, last, prev_fd);
	if (curr == last)
	{
		//printf("redirects curr=last: curr %d\n", curr);
		ft_dup_close(prev_fd, STDIN_FILENO);
		if (shell->outfile)
			ft_setup_redir_out(shell);	
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		close(shell->fd[0]);
		close(shell->fd[1]);
	}
	else if (curr == 0)
	{
		//printf("\n\n\nredirects: curr %d last %d, prev_fd %d\n", curr, last, prev_fd);
		if (shell->infile)
		{
			//printf("\n\n\nredirects: curr %d last %d, prev_fd %d\n", curr, last, prev_fd);
			ft_setup_redir_in(shell);
		}
		//printf("\n\n\nredirects: curr %d last %d, prev_fd %d\n", curr, last, prev_fd);
		ft_dup_close(shell->fd[1], STDOUT_FILENO);
		//printf("\n\n\nredirects: curr %d last %d, prev_fd %d\n", curr, last, prev_fd);
		close(shell->fd[0]);
	}
	else if (shell->fd_in <= 0)
	{
		ft_dup_close(prev_fd, STDIN_FILENO);
		ft_dup_close(shell->fd[1], STDOUT_FILENO);
		close(shell->fd[0]);
	}
	//printf("redirects return: shell->status = %d", shell->status);
	return (shell->status);
}

int	ft_setup_redirects(t_shell *shell)
{
	if (shell->infile)
	{
		//printf("redirects infile\n\n");
		ft_setup_redir_in(shell);
	}
	if (shell->outfile)
	{
		//printf("redirects outfile\n\n");
		ft_setup_redir_out(shell);
	}
	return (shell->status);
}
