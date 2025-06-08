/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:14:09 by gapachec          #+#    #+#             */
/*   Updated: 2025/06/07 20:31:25 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Includes padrão e libft*/
# include "../libft/include/libft.h" 
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

/* Includes dos módulos */
# include "token.h"
# include "parser.h"

/**
 * @brief Represents the state of the shell.
 *
 * Holds the environment variables and the exit status of the last executed command.
 * 
 * char **envp = Array of environment variables.
 * 
 * int  last_exit_status = Exit status of the last executed command.
 */
typedef struct s_shell
{
	char	**envp;
	int		last_exit_status;
	int		fd_in;
	int		fd_out;
	int		fd[2];
	char	*infile;
	char	*outfile;
}	t_shell;

int		main(int argc, char **argv, char **envp);
void	ft_start_minishell(t_shell *shell);
void	ft_handle_signals(void);
void	ft_cleanup(char *input);
void	ft_init_struct(t_shell *shell, char **envp);

int		ft_error_execve(t_shell *shell);
int		ft_error(int code, char *str);
void	ft_free_split(char **split);
int		ft_exec_simplecmd(t_shell *shell, t_command *cmd);
void	ft_exec_cmds(t_shell *shell, t_command *cmds);

void	ft_closefd(t_shell *shell);
int		ft_handle_pid(t_shell *shell, t_command *cmd, int curr_cmd, int last_cmd);
int		ft_handle_middlecmd(t_shell *shell, t_command *cmd);
int		ft_handle_lastcmd(t_shell *shell, t_command *cmd);
int		ft_exec_cmdpipe(t_shell *shell, t_command *cmd, int n_cmd);

char	*ft_get_cmdpath(char *cmd, char **envp);

void	ft_print_commands(t_shell *shell, t_command *cmd);
void	ft_print_tokens(t_token *tokens);

#endif
