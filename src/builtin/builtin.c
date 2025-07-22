/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:04:01 by gapachec          #+#    #+#             */
/*   Updated: 2025/07/22 17:52:42 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (
		ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0
	);
}

void	exec_builtin(char **args, t_shell *shell)
{
		if (ft_strcmp(*args, "echo") == 0)
		shell->last_exit_status = builtin_echo(args);
	else if (ft_strcmp(*args, "cd") == 0)
		builtin_cd(args, shell);
	else if (ft_strcmp(*args, "pwd") == 0)
		shell->last_exit_status = builtin_pwd();
	else if (ft_strcmp(*args, "export") == 0)
		builtin_export(args, &shell->envp, shell);
	else if (ft_strcmp(*args, "unset") == 0)
		builtin_unset(args, &shell->envp);
	else if (ft_strcmp(*args, "env") == 0)
		shell->last_exit_status = builtin_env(shell->envp);
	else if (ft_strcmp(*args, "exit") == 0)
		builtin_exit(args, shell);
}
