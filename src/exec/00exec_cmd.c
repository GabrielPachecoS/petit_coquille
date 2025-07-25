/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00exec_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:35:20 by jucoelho          #+#    #+#             */
/*   Updated: 2025/07/24 20:31:53 by jucoelho         ###   ########.fr       */
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

void	ft_exec_command(t_shell *shell, t_command *cmd)
{
	char	**env_array;
	char	*fullpath;

	env_array = env_to_array(shell->envp);
	fullpath = ft_get_cmdpath(cmd->argv[0], shell->envp);
	if (!fullpath)
	{
		ft_free_split(env_array);
		printf("exec cmd command not found");
		exit(1);
	}
	int i = 0;
	while (cmd->argv[i])
	{
		i++;
	}
	execve(fullpath, cmd->argv, env_array);
	perror("execve failed");
	ft_free_split(env_array);
	free(fullpath);
	exit(EXIT_FAILURE);
}
int	ft_exec_cmdpipe(t_shell *shell, t_command *cmd, int n_cmd)
{
	int	*pid;
	int	status;
	int	i;

	i = 0;
	pid = malloc(sizeof(int) * (n_cmd + 1));
	if (!pid)
		return (ft_error(1, "malloc failed"));
	status = ft_loop_cmdpipe(shell, cmd, pid, n_cmd);
	while (i < n_cmd)
	{
		if (i == n_cmd - 1)
			waitpid(pid[i], &status, 0);
		else
			waitpid(pid[i], NULL, 0);
		i++;
	}
	free(pid);
	shell->status = status >> 8;
	return (status >> 8);
}

int	ft_exec_simplecmd(t_shell *shell, t_command *cmd)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		ft_setup_redirects(shell);
		ft_exec_command(shell, cmd);
	}
	else
	{
		waitpid(pid, &status, 0);
		shell->status = WEXITSTATUS(status);
	}
	return (shell->status);
}
void	ft_exec_cmds(t_shell *shell, t_command *cmds)
{
	int	n_cmds = ft_listsize(cmds);
	
	//if (ft_isbuiltin(shell, cmds)); fazer função para verificar se é builtin
	//lembrar: se for simple command não pode fazer fork
	
	
	if (!cmds->next)
		shell->last_exit_status = ft_exec_simplecmd(shell, cmds);
	else
	{
		shell->last_exit_status = ft_exec_cmdpipe(shell, cmds, n_cmds);
	}
}
