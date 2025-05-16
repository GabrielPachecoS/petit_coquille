/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:13:33 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/16 11:01:49 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

// Estrutura que representa um comando completo (ex: ls -l > out.txt)
typedef struct s_command
{
	char			**argv;           // Lista de argumentos do comando (argv[0] = comando)
	int				redir_in;         // Redirecionador de entrada (0 = nenhum, 1 = '<', 2 = '<<')
	char			*redir_in_file;   // Nome do arquivo de entrada
	int				redir_out;        // Redirecionador de saída (0 = nenhum, 1 = '>', 2 = '>>')
	char			*redir_out_file;  // Nome do arquivo de saída
	struct s_command	*next;        // Ponteiro para próximo comando (em caso de pipe)
}	t_command;

// Protótipos das funções do parser
t_command	*parser(t_token *tokens);   // Transforma tokens em comandos
void		free_commands(t_command *cmd); // Libera lista de comandos
void		print_commands(t_command *cmd); // Imprime comandos (debug)

#endif
