/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:25:24 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/23 15:02:37 by jucoelho         ###   ########.fr       */
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
t_token	*ft_lexer(char *input);	// Recebe a linha de input e retorna lista de tokens
int		ft_handle_token(char *input, int i, t_token **tokens);
void	ft_print_tokens(t_token *tokens); // Imprime tokens para debug
void	ft_free_tokens(t_token *tokens);  // Libera a memória dos tokens

#endif
