/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:13:33 by gapachec          #+#    #+#             */
/*   Updated: 2025/08/19 03:22:13 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_shell t_shell;

/**
 * @brief Represents a single command and its execution context.
 *
 * Contains arguments, redirection information, and links to next command
 * (for pipelines).
 *
 * char              **argv = Argument list for the command.
 *
 * int               redir_in = Flag for input redirection.
 *
 * char              *redir_infile = Input redirection filename.
 *
 * int               redir_out = Flag for output redirection.
 *
 * char              *redir_outfile = Output redirection filename.
 *
 * struct s_command  *next = Pointer to the next command.
 */
typedef struct s_command
{
	char				**argv;
	t_redirect			*redir_in;
	t_redirect			*redir_out;
	int					fd_in;
	int					fd_out;
	struct s_command	*next;
}	t_command;

typedef struct s_redirect
{
	char				*value;
	struct s_command	*next;
}	t_redirect;

t_command	*ft_parser(t_token *tokens, t_shell *shell);
void		ft_free_commands(t_command *cmd);
int			ft_parser_pipe(t_command **cmd);
int			ft_parser_redir_out(t_shell *shell, t_command *cmd, t_token **tok);
int			ft_parser_redir_in(t_shell *shell, t_command *cmd, t_token **tok);
t_command	*ft_new_command(void);
void		ft_heredoc(t_shell *shell, int fd);

#endif
