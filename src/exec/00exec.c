/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:34:42 by jucoelho          #+#    #+#             */
/*   Updated: 2025/07/22 17:53:02 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Calculates the number of nodes in a command list.
 *
 * Iterates through the linked list of commands to count its length.
 *
 * @param cmds Pointer to the first command in the list.
 *
 * @return Number of command nodes in the list.
 */
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

/**
 * @brief Handles errors during execve execution.
 *
 * Closes relevant file descriptors and prints an error message
 * before exiting the process with failure.
 *
 * @param shell Pointer to the shell structure containing file descriptors.
 *
 * @return This function does not return (calls exit).
 */
int	ft_error_execve(t_shell *shell)
{
    close(shell->fd[0]);
    close(shell->fd[1]);
    close(shell->fd_in);
    close(shell->fd_out);
    perror("execve failed");
    exit(EXIT_FAILURE);
}

/**
 * @brief Prints an error message and exits the program.
 *
 * Uses perror to print the given error message and exits with the provided code.
 *
 * @param code Exit status code.
 * @param str  Error message to be printed.
 *
 * @return This function does not return (calls exit).
 */
int	ft_error(int code, char *str)
{
    perror(str);
    exit(code);
}

/**
 * @brief Frees a NULL-terminated array of strings.
 *
 * Iterates over the array, freeing each string and then the array itself.
 *
 * @param split Pointer to the array of strings.
 */
void	ft_free_split(char **split)
{
    int	i = 0;
    if (!split)
        return;
    while (split[i])
        free(split[i++]);
    free(split);
}

/**
 * @brief Executes a single command, handling both built-ins and external binaries.
 *
 * Converts the environment list to an array, resolves the command path,
 * and executes the command using execve. If the command is a built-in,
 * it is executed directly and the process exits with the resulting status.
 *
 * @param shell Pointer to the shell structure.
 * @param cmd   Pointer to the command to be executed.
 */
static void	exec_command(t_shell *shell, t_command *cmd)
{
	char	**env_array;
	char	*fullpath;

	if (is_builtin(cmd->argv[0]))
	{
		exec_builtin(cmd->argv, shell);
		exit(shell->last_exit_status);
	}
	fullpath = ft_get_cmdpath(cmd->argv[0], shell->envp);
	if (!fullpath)
	{
		ft_putstr_fd("command not found\n", 2);
		exit(127);
	}
	env_array = env_to_array(shell->envp);
	execve(fullpath, cmd->argv, env_array);
	perror("execve");
	ft_free_split(env_array);
	free(fullpath);
	exit(EXIT_FAILURE);
}


/**
 * @brief Executes a single command in a child process.
 *
 * Forks the process and runs the given command. Waits for the child
 * process to complete and returns its exit status.
 *
 * @param shell Pointer to the shell structure.
 * @param cmd   Pointer to the command to be executed.
 *
 * @return Exit status of the executed command.
 */
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
    return (status >> 8);
}

/**
 * @brief Entry point for executing a list of commands.
 *
 * Determines if the command list contains a single command or a pipeline.
 * Calls the appropriate execution function and updates the shell's
 * last exit status.
 *
 * @param shell Pointer to the shell structure.
 * @param cmds  Pointer to the head of the command list.
 */
void	ft_exec_cmds(t_shell *shell, t_command *cmds)
{
    int	n_cmds = ft_listsize(cmds);
    if (!cmds->next)
        shell->last_exit_status = ft_exec_simplecmd(shell, cmds);
    else
        shell->last_exit_status = ft_exec_cmdpipe(shell, cmds, n_cmds);
}
