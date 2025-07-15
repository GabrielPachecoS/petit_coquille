/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:05:35 by gapachec          #+#    #+#             */
/*   Updated: 2025/07/15 18:09:39 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

void	ft_exec_cmds(t_shell *shell, t_command *cmds);
int	ft_exec_simplecmd(t_shell *shell, t_command *cmd);
void	ft_free_split(char **split);
int	ft_error(int code, char *str);
int	ft_error_execve(t_shell *shell);

void	ft_closefd(t_shell *shell);
int	ft_exec_cmdpipe(t_shell *shell, t_command *cmd, int n_cmd);
int	ft_loop_cmdpipe(t_shell *shell, t_command *cmd, int *pid, int n_cmd);
int	ft_handle_pid(t_shell *shell, t_command *cmd, int curr, int last, int prev_fd);
char	*ft_get_cmdpath(char *cmd, t_env *env);

#endif
