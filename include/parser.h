/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:13:33 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/28 12:50:30 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

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
 * char              *redir_in_file = Input redirection filename.
 * 
 * int               redir_out = Flag for output redirection.
 * 
 * char              *redir_out_file = Output redirection filename.
 * 
 * struct s_command  *next = Pointer to the next command.
 */
typedef struct s_command
{
	char				**argv;
	int					redir_in;
	char				*redir_in_file;
	int					redir_out;
	char				*redir_out_file;
	struct s_command	*next;
}	t_command;

t_command	*ft_parser(t_token *tokens);
void		ft_free_commands(t_command *cmd);
void		ft_print_commands(t_command *cmd);
int			ft_parser_pipe(t_command **cmd);
int			ft_parser_redir_out(t_command *cmd, t_token **tok);
int			ft_parser_redir_in(t_command *cmd, t_token **tok);
t_command	*ft_new_command(void);

#endif
