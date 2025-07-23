/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:04:01 by gapachec          #+#    #+#             */
/*   Updated: 2025/07/16 16:18:15 by jucoelho         ###   ########.fr       */
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

int	exec_builtin(t_shell *shell, char **args, t_env **env, int *status)
{
	if (!args[0])
		return (0);
	if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(shell, args));
	if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args, env));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(args[0], "export") == 0)
		return (builtin_export(args, env));
	if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset(args, env));
	if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env(*env));
	if (ft_strcmp(args[0], "exit") == 0)
		builtin_exit(args, status);
	return (0);
}
