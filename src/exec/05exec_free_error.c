/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05exec_free_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:22:46 by jucoelho          #+#    #+#             */
/*   Updated: 2025/07/24 17:04:19 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	ft_error_execve(t_shell *shell)
{
	close(shell->fd[0]);
	close(shell->fd[1]);
	close(shell->fd_in);
	close(shell->fd_out);
	perror("execve failed");
	exit(EXIT_FAILURE);
}

int	ft_error(int code, char *str)
{
	//printf("entrou ft_error\n");
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