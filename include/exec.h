/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:05:35 by gapachec          #+#    #+#             */
/*   Updated: 2025/08/19 04:03:22 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXEC_H
# define EXEC_H
# include "minishell.h"
//00exec_cmd
void	ft_exec(t_shell *shell, t_command *cmds);
int		ft_exec_simplecmd(t_shell *shell, t_command *cmd);
int		ft_exec_cmdpipe(t_shell *shell, t_command *cmd, int n_cmd);
//static int list size
void	ft_exec_command(t_shell *shell, t_command *cmd);
//no futuro is builtin
//no futuro exec builtin

//01exec
int	ft_setup_redirects(t_shell *shell, t_command *cmd);
int	ft_setup_redirects_pipe(t_shell *shell, t_command *cmd, int curr, int last);
//02exec

int	ft_dup_close(int close_fd, int dup_fd);
int	ft_close_reset(int close_fd);
//03exec
int	ft_setup_fork(t_shell *shell,  t_command *cmds, int *pid, int i);
int		ft_loop_cmdpipe(t_shell *shell, t_command *cmd, int *pid, int n_cmd);
int		ft_handle_pid(t_shell *shell, int curr, int last, int prev_fd);
void	ft_close_fd(t_shell *shell);

//04exec_path
char	*ft_get_cmdpath(char *cmd, t_env *env);
//static char	*ft_search_cmd_in_paths(char **paths, char *cmd)
//static char	*ft_get_path_variable(t_env *env)
//static char	*ft_build_fullpath(char *path, char *cmd)
//static char	*ft_report_cmd_not_found(char *cmd)

//05exec_free_error
void	ft_free_split(char **split);
int		ft_error(int code, char *str);
int		ft_error_execve(t_shell *shell);

#endif
