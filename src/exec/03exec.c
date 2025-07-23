/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 21:16:22 by jucoelho          #+#    #+#             */
/*   Updated: 2025/07/22 21:33:43 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_setup_fork(t_shell *shell, int *pid, int i)
{
	if (pipe(shell->fd) < 0)
			return (ft_error(1, "pipe failed"));
	pid[i] = fork();
	if (pid[i] < 0)
		return (ft_error(1, "fork failed"));
	return(1);
}