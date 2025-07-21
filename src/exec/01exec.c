/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:21:37 by jucoelho          #+#    #+#             */
/*   Updated: 2025/07/21 17:22:02 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_setup_redirects(t_shell *shell)
{
	if (shell->fd_in > 0)
	{
		shell->fd_in = open(shell->infile, O_RDONLY);
		if (shell->fd_in < 0)
			perror(shell->infile); 
		dup2(shell->fd_in, STDIN_FILENO);	
	}
	if (shell->fd_out > 0)
	{
		if (shell->append > 0)
			shell->fd_out = open(shell->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (shell->fd_out > 0)
			shell->fd_out = open(shell->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);	
		if (shell->fd_out < 0)
			perror(shell->outfile);
		dup2(shell->fd_out, STDOUT_FILENO);	
	}
	return (1);
}