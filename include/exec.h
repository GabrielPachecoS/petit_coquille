/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:05:35 by gapachec          #+#    #+#             */
/*   Updated: 2025/07/21 17:41:59 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
//00exec_cmd
void	ft_exec_cmds(t_shell *shell, t_command *cmds);
int		ft_exec_simplecmd(t_shell *shell, t_command *cmd);
int		ft_exec_cmdpipe(t_shell *shell, t_command *cmd, int n_cmd);
//static int list size
//static int exec_command
//no futuro is builtin
//no futuro exec builtin

//01exec
int	ft_setup_redirects(t_shell *shell);
//02exec

//03exec
int		ft_handle_pid1(t_shell *shell, t_command *cmd);
void	ft_closefd(t_shell *shell);
int		ft_loop_cmdpipe(t_shell *shell, t_command *cmd, int *pid, int n_cmd);
int		ft_handle_pid(t_shell *shell, t_command *cmd, int curr, int last, int prev_fd);
void	setup_redirects(int in_fd, int out_fd);
int		ft_handle_simplecmd(t_shell *shell, t_command *cmd);

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
