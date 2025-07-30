/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:14:09 by gapachec          #+#    #+#             */
/*   Updated: 2025/07/30 15:49:58 by jucoelho         ###   ########.fr       */
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
# include "env.h"
# include "builtin.h"

/**
 * @brief Represents the state of the shell.
 *
 * Holds the environment variables and the exit status of the last executed command.
 *
 * t_env	envp = Linked list of environment variables.
 *
 * int  last_exit_status = Exit status of the last executed command.
 */
typedef struct s_shell
{
	t_env	*envp;
	int		last_exit_status;
	int		fd_in;
	int		fd_out;
	int		fd[2];
	int		append;
	int		status;
	int		should_exit;
	int		exit_code;
	char	*heredoc;
	char	*infile;
	char	*outfile;
}	t_shell;

# include "exec.h"

int		main(int argc, char **argv, char **envp);
void	ft_start_minishell(t_shell *shell);
void	ft_handle_signals(void);
void	ft_cleanup(t_shell *shell, char *input);
void	ft_init_struct(t_shell *shell, char **envp);
void	ft_print_commands(t_shell *shell, t_command *cmd);
void	ft_print_tokens(t_token *tokens);
void	ft_free_shell(t_shell *shell);
void	ft_read_heredoc(t_shell *shell, int fd);
#endif
