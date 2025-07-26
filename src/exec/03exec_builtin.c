/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03exec_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 21:16:22 by jucoelho          #+#    #+#             */
/*   Updated: 2025/07/25 18:30:51 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

if (ft_is_builtin(shell, cmds))
//fazer função para verificar se é builtin
//lembrar: se for simple command não pode fazer fork
{
	if (!cmds->next)
		shell->last_exit_status = ft_exec_simplebuiltin(shell, cmds);
	else
	{
		shell->last_exit_status = ft_exec_cmdbuiltin(shell, cmds, n_cmds);
	}
}

int	ft_exec_simplebuiltin(t_shell *shell, t_command *cmd)
{
	int	status;

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
