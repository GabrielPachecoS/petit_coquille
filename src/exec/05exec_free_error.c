/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05exec_free_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:22:46 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/16 20:03:15 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_execve(t_shell *shell)
{
	if (shell->fd[0] > 0)
		ft_close_reset(shell->fd[0]);
	if (shell->fd[0] > 0)
		ft_close_reset(shell->fd[1]);
	if (shell->fd[0] > 0)
		ft_close_reset(shell->prev_fd);
	perror("execve failed");
	exit(EXIT_FAILURE);
}

int	ft_error(int code, char *str)
{
	perror(str);
	exit(code);
}

void	ft_free_split(char **split)
{
	int	i = 0;
	if (!split)
		return;
	while (split[i])
		free(split[i++]);
	free(split);
}