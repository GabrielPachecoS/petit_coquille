/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:34:42 by jucoelho          #+#    #+#             */
/*   Updated: 2025/07/02 22:59:33 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_cmds(t_shell *shell, t_command *cmds)
{
	t_command	*current;

	current = cmds;
	if (is_builtin(cmds->argv[0]))
	{
		shell->last_exit_status = exec_builtin(cmds->argv, &shell->envp,
			&shell->last_exit_status);
		return ;
	}
	while (current)
	{
		ft_exec_simplecmd(shell, current);
		current = current ->next;
	}
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
