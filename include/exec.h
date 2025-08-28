/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:05:35 by gapachec          #+#    #+#             */
/*   Updated: 2025/08/28 15:48:26 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "minishell.h"

//00exec_cmd
void	ft_exec(t_shell *shell, t_command *cmds);
int		ft_exec_simplecmd(t_shell *shell, t_command *cmd);
int		ft_exec_cmdpipe(t_shell *shell, t_command *cmd, int n_cmd);
void	ft_exec_command(t_shell *shell, t_command *cmd);

//01exec
int		ft_setup_fork(t_shell *shell, t_command *cmds, int *pid, int i);
int		ft_dup_close(int close_fd, int dup_fd);
int		ft_close_reset(int *close_fd);
int		ft_loop_cmdpipe(t_shell *shell, t_command *cmd, int *pid, int n_cmd);

//02exec_redir
int		ft_setup_redirects(t_shell *shell, t_command *cmd);
int		ft_setup_redirects_pipe(
			t_shell *shell, t_command *cmd, int curr, int last);
int		ft_setup_redir_in(t_command *cmd);
int		ft_setup_redir_out(t_shell *shell, t_command *cmd);

//03exec_redir
void	ft_setup_last(t_shell *shell, t_command *cmd);
void	ft_setup_first(t_shell *shell, t_command *cmd);
void	ft_setup_middle(t_shell *shell, t_command *cmd);

//04exec_path
char	*ft_get_cmdpath(char *cmd, t_env *env);

//05exec_free_error
void	ft_free_split(char **split);
int		ft_error(int code, char *str);
int		ft_error_execve(t_shell *shell);

#endif
