/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:35:20 by jucoelho          #+#    #+#             */
/*   Updated: 2025/07/19 23:16:28 by jucoelho         ###   ########.fr       */
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

int	ft_handle_simplecmd(t_shell *shell, t_command *cmd)
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
	exec_command(shell, cmd);
	return (1);
}
int	ft_exec_simplecmd(t_shell *shell, t_command *cmd)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		ft_handle_simplecmd(shell, cmd);
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
	if (!cmds->next)
		shell->last_exit_status = ft_exec_simplecmd(shell, cmds);
	else
		shell->last_exit_status = ft_exec_cmdpipe(shell, cmds, n_cmds);
}
