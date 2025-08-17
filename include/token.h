/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:25:24 by gapachec          #+#    #+#             */
/*   Updated: 2025/08/16 20:14:53 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

/**
 * @brief Enumeration of possible token types.
 * 
 * Defines the categories of tokens that the lexer can recognize in shell input.
 * 
 * T_WORD = A word token (e.g., command or argument).
 * 
 * T_PIPE = A pipe symbol '|', used for piping commands.
 * 
 * T_REDIR_IN = Input redirection '<'.
 * 
 * T_REDIR_OUT = Output redirection '>'.
 * 
 * T_REDIR_APPEND = Output append redirection '>>'.
 * 
 * T_HEREDOC = Heredoc redirection '<<'.
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

/**
 * @brief Represents a token from the lexer.
 *
 * Each token contains a type, value, and pointer to the next token in the list.
 * 
 * t_token_type    type = The type of the token.
 * 
 * char            value = The actual string value of the token.
 * 
 * struct s_token  next = Pointer to the next token.
 */
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_shell t_shell;

//lexer
t_token	*ft_lexer(char *input);

//utils
int		ft_is_operator(char c);
int		ft_is_special_char(char c);

//tokens
int		ft_add_simple_token(t_token **tokens, t_token_type type, char *input, int i, int size);
void	ft_add_token(t_token **list, t_token *new);
t_token	*ft_new_token(t_token_type type, char *value);
void	ft_free_tokens(t_token *tokens);

//handle
int		ft_handle_token(char *input, int i, t_token **tokens);
int		ft_handle_word(char *input, int i, t_token **tokens);

//int		ft_handle_quoted(char *input, int i, t_token **tokens, char quote);
//char	*ft_handle_escaped_char(const char *input, int *i);
//void	ft_print_tokens(t_token *tokens);
//int		ft_expandvar(char *input, t_shell *shell, t_token **tokens);
//int		ft_handle_braces(char *input, t_shell *shell, t_token **tokens);
//int		ft_handle_expalnum(char *input, t_shell *shell, t_token **tokens);
//int		ft_handle_expander(char *input, int i, t_shell *shell, t_token **tokens);

#endif
