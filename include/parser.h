/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:13:33 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/25 23:28:40 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

// Estrutura que representa um comando completo (ex: ls -l > out.txt)
typedef struct s_command
{
	char				**argv;
	int					redir_in;
	char				*redir_in_file;
	int					redir_out;
	char				*redir_out_file;
	struct s_command	*next;
}	t_command;

// Protótipos das funções do parser
t_command	*ft_parser(t_token *tokens);
void		ft_free_commands(t_command *cmd);
void		ft_print_commands(t_command *cmd);
int			ft_parser_pipe(t_command **cmd);
int			ft_parser_redir_out(t_command *cmd, t_token **tok);
int			ft_parser_redir_in(t_command *cmd, t_token **tok);
t_command	*ft_new_command(void);

#endif
