/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:35:20 by jucoelho          #+#    #+#             */
/*   Updated: 2025/07/16 16:55:26 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_listsize(t_command *cmds)
{
	int	nbr_nodes = 0;
	while (cmds)
	{
	cmds = cmds->next;
		nbr_nodes++;
	}
	return (nbr_nodes);
}

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

static void	exec_command(t_shell *shell, t_command *cmd)
{
	char	**env_array;
	char	*fullpath;

	env_array = env_to_array(shell->envp);
	fullpath = ft_get_cmdpath(cmd->argv[0], shell->envp);
	if (!fullpath)
	{
		ft_free_split(env_array);
		perror("command not found");
		exit(127);
	}
	execve(fullpath, cmd->argv, env_array);
	perror("execve failed");
	ft_free_split(env_array);
	free(fullpath);
	exit(EXIT_FAILURE);
}

int	ft_exec_simplecmd(t_shell *shell, t_command *cmd)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (ft_error(1, "fork failed"));
	if (pid == 0)
		exec_command(shell, cmd);
	waitpid(pid, &status, 0);
	shell->status = status >> 8;
	return (status >> 8);
}

void	ft_exec_cmds(t_shell *shell, t_command *cmds)
{
	int	n_cmds = ft_listsize(cmds);

	if (!cmds->next)
		shell->last_exit_status = ft_exec_simplecmd(shell, cmds);
	else
		shell->last_exit_status = ft_exec_cmdpipe(shell, cmds, n_cmds);
}
