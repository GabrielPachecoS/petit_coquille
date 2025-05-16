/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:14:09 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/16 10:19:54 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Includes padrão */
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

/* Estrutura principal do shell */
typedef struct s_shell
{
	char	**envp;
	int		last_exit_status;
}	t_shell;

/* Protótipos */
void	start_minishell(t_shell *shell);
void	handle_signals(void);
void	cleanup(char *input);

#endif
