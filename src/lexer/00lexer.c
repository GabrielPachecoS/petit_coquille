/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:24:58 by gapachec          #+#    #+#             */
/*   Updated: 2025/08/28 16:36:58 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_syntax_errors(t_shell *shell, t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	if (curr->type == T_PIPE)
	{
		shell->status = 2;
		return (printf("Syntax error: pipe at the beginning\n"), 1);
	}
	while (curr)
	{
		if (curr->type == T_PIPE)
		{
			if (!curr->next || curr->next->type == T_PIPE)
				return (shell->status = 2,
					printf("Syntax error: misplaced pipe\n"), 1);
		}
		else if (curr->type == T_REDIR_IN || curr->type == T_REDIR_OUT
			|| curr->type == T_HEREDOC || curr->type == T_REDIR_APPEND)
		{
			if (!curr->next || curr->next->type != T_WORD)
				return (printf("Error: redirection without argument\n"), 1);
		}
		curr = curr->next;
	}
	return (0);
}

/*
 * @brief Lexical analyzer that converts 
 an input string into a list of tokens.
 *
 * Iterates over the input string and 
 * splits it into meaningful tokens,
 * handling escaped characters, quoted 
 * strings, operators (e.g., pipes and
 * redirections), and words. 
 * Each identified token is added to a linked list.
 *
 * @param input The raw command line input string.
 *
 * @return Pointer to the head of the token list,
 * or NULL if no tokens were found.
 */
t_token	*ft_lexer(char *input)
{
	int		i;
	t_token	*tokens;
	char	*escaped;

	i = 0;
	tokens = NULL;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		if (!input[i])
			break ;
		else if (input[i] == '\\' && input[i + 1])
		{
			escaped = ft_handle_escaped_char(input, &i);
			ft_add_token(&tokens, ft_new_token(T_WORD, escaped));
		}
		else if (ft_is_operator(input[i]))
			i = ft_handle_token(input, i, &tokens);
		else
			i = ft_handle_word(input, i, &tokens);
		if (i < 0)
			break ;
	}
	return (tokens);
}
