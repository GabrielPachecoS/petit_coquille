/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:25:24 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/25 23:02:55 by gapachec         ###   ########.fr       */
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
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC
}	t_token_type;

/*
 * Estrutura de um token.
 * Contém o tipo do token, seu valor (string) e ponteiro para o próximo token 
 * da lista.
 */
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

// Protótipos das funções do lexer:
t_token	*ft_lexer(char *input);
int		ft_handle_token(char *input, int i, t_token **tokens);
t_token	*ft_new_token(t_token_type type, char *value);
void	ft_add_token(t_token **list, t_token *new);
void	ft_print_tokens(t_token *tokens);
void	ft_free_tokens(t_token *tokens);

#endif
