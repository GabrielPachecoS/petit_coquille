/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:34:42 by jucoelho          #+#    #+#             */
/*   Updated: 2025/06/11 21:20:07 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_listsize(t_command *cmds)
{
	int	nbr_nodes;

	nbr_nodes = 0;
	while (cmds)
	{
		cmds = cmds->next;
		nbr_nodes++;
	}
	return (nbr_nodes);
}
int	ft_error_execve(t_command *cmd)
{
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	close(cmd->fd_in);
	close(cmd->fd_out);
	perror("execve failed");
	exit(EXIT_FAILURE);
}

int	ft_error(int code, char *str)
{
	perror(str);
	exit(code);
}

int	ft_exec_simplecmd(t_shell *shell, t_command *cmd)
{
	int		pid;
	int		status;
	char	*fullpath;

	fullpath = ft_get_cmdpath(cmd->argv[0], shell->envp);
	if (!fullpath)
	{
		perror("command not found");
		return (127);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		execve(fullpath, cmd->argv, shell->envp);
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	free(fullpath);
	return (status >> 8);
}

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_exec_cmds(t_shell *shell, t_command *cmds)
{
	int	n_cmds;
	
	n_cmds = ft_listsize(cmds);
	shell->fd = malloc(sizeof(int *) * (n_cmds));
	if (cmds->next == NULL)
		ft_exec_simplecmd(shell, cmds);
	else
		ft_exec_cmdpipe(shell, cmds, n_cmds);
}

