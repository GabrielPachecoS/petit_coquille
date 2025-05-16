/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:25:24 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/16 11:02:57 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

/*
 * Enumeração dos tipos de token que o lexer pode identificar.
 * Cada tipo representa uma categoria de símbolo no shell.
 */
typedef enum e_token_type
{
	T_WORD,			// Palavra comum (comando ou argumento)
	T_PIPE,			// Pipe '|'
	T_REDIR_IN,		// Redirecionador de entrada '<'
	T_REDIR_OUT,	// Redirecionador de saída '>'
	T_REDIR_APPEND,	// Redirecionador de saída em append '>>'
	T_HEREDOC		// Heredoc '<<'
}	t_token_type;

/*
 * Estrutura de um token.
 * Contém o tipo do token, seu valor (string) e ponteiro para o próximo token da lista.
 */
typedef struct s_token
{
	t_token_type	type;		// Tipo do token
	char			*value;		// Valor associado (string)
	struct s_token	*next;		// Próximo token na lista encadeada
}	t_token;

// Protótipos das funções do lexer:
t_token	*lexer(char *input);           // Recebe a linha de input e retorna lista de tokens
void	print_tokens(t_token *tokens); // Imprime tokens para debug
void	free_tokens(t_token *tokens);  // Libera a memória dos tokens

#endif
