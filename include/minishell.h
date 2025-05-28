/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:14:09 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/28 11:36:23 by gapachec         ###   ########.fr       */
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
 * char	**envp = Array of environment variables.
 * 
 * int	last_exit_status = Exit status of the last executed command.
 */
typedef struct s_shell
{
	char	**envp;
	int		last_exit_status;
}	t_shell;

int		main(int argc, char **argv, char **envp);
void	ft_start_minishell(t_shell *shell);
void	ft_handle_signals(void);
void	ft_cleanup(char *input);
void	ft_exec_cmds(t_shell *shell, t_command *cmds);
int		ft_exec_simplecmd(t_shell *shell, t_command *cmd);
char	*ft_get_cmdpath(char *cmd, char **envp);
void	ft_free_split(char **split);

#endif
