/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:57:17 by jucoelho          #+#    #+#             */
/*   Updated: 2025/06/07 20:09:02 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_closefd(t_shell *shell)
{
    close(shell->fd[0]);
    close(shell->fd[1]);
    close(shell->fd_in);
    close(shell->fd_out);
}

static void	handle_exec(t_shell *shell, t_command *cmd)
{
    char	**envp;
    char	*fullpath;

    envp = env_to_array(shell->envp);
    fullpath = ft_get_cmdpath(cmd->argv[0], shell->envp);
    if (execve(fullpath, cmd->argv, envp) == -1)
        ft_error_execve(shell);
}

static void	setup_redirects(int in_fd, int out_fd)
{
    dup2(in_fd, STDIN_FILENO);
    dup2(out_fd, STDOUT_FILENO);
    close(in_fd);
    close(out_fd);
}

int	ft_handle_pid(t_shell *shell, t_command *cmd, int curr, int last)
{
    if (curr == 0)
    {
        setup_redirects(shell->fd_in, shell->fd[1]);
        close(shell->fd[0]);
        handle_exec(shell, cmd);
    }
    else if (curr < last)
    {
        setup_redirects(shell->fd[0], shell->fd[1]);
        handle_exec(shell, cmd);
    }
    else
    {
        setup_redirects(shell->fd[0], shell->fd_out);
        close(shell->fd[1]);
        handle_exec(shell, cmd);
    }
    return (1);
}

int	ft_exec_cmdpipe(t_shell *shell, t_command *cmd, int n_cmd)
{
    int	*pid;
    int	i;
    int	status;

    pid = malloc(sizeof(int) * (n_cmd + 1));
    if (!pid)
        return (ft_error(1, "malloc failed"));
    i = 0;
    while (cmd)
    {
        if (pipe(shell->fd) < 0)
            return (ft_error(1, "pipe failed"));
        pid[i] = fork();
        if (pid[i] < 0)
            return (ft_error(1, "fork failed"));
        if (pid[i] == 0)
            ft_handle_pid(shell, cmd, i, n_cmd - 1);
        close(shell->fd[1]);
        if (i > 0)
            close(shell->fd[0]);
        cmd = cmd->next;
        i++;
    }
    ft_closefd(shell);
    i = 0;
    while (i < n_cmd)
        waitpid(pid[i++], NULL, 0);
    waitpid(pid[n_cmd], &status, 0);
    free(pid);
    return (status >> 8);
}
