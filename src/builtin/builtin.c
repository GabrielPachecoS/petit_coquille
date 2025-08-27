/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:04:01 by gapachec          #+#    #+#             */
/*   Updated: 2025/08/27 16:08:25 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(t_command *cmds)
{
	if (cmds == NULL || cmds->argv == NULL || cmds->argv[0] == NULL)
		return (0);
	return (
		ft_strcmp(cmds->argv[0], "echo") == 0
		|| ft_strcmp(cmds->argv[0], "cd") == 0
		|| ft_strcmp(cmds->argv[0], "pwd") == 0
		|| ft_strcmp(cmds->argv[0], "export") == 0
		|| ft_strcmp(cmds->argv[0], "unset") == 0
		|| ft_strcmp(cmds->argv[0], "env") == 0
		|| ft_strcmp(cmds->argv[0], "exit") == 0
	);
}

void	ft_exec_simplebuiltin(t_shell *shell, char **args)
{
	if (ft_strcmp(*args, "echo") == 0)
	{
		shell->status = ft_builtin_echo(args);
	}
	else if (ft_strcmp(*args, "cd") == 0)
		ft_builtin_cd(args, shell);
	else if (ft_strcmp(*args, "pwd") == 0)
		shell->status = ft_builtin_pwd();
	else if (ft_strcmp(*args, "export") == 0)
		ft_builtin_export(args, &shell->envp, shell);
	else if (ft_strcmp(*args, "unset") == 0)
		ft_builtin_unset(args, &shell->envp);
	else if (ft_strcmp(*args, "env") == 0)
		shell->status = ft_builtin_env(shell->envp);
	else if (ft_strcmp(*args, "exit") == 0)
		ft_builtin_exit(args, shell);
}
