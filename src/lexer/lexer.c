/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:24:58 by gapachec          #+#    #+#             */
/*   Updated: 2025/08/11 22:29:38 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

/**
 * @brief Lexical analyzer that converts an input string into a list of tokens.
 *
 * Iterates over the input string and splits it into meaningful tokens,
 * handling escaped characters, quoted strings, operators (e.g., pipes and
 * redirections), and words. Each identified token is added to a linked list.
 *
 * @param input The raw command line input string.
 *
 * @return Pointer to the head of the token list, or NULL if no tokens were found.
 */
t_token	*ft_lexer(char *input, t_shell *shell)
{
	int		i;
	t_token	*tokens;
	char	*escaped;

	i = 0;
	tokens = NULL;
	printf("\n\n\ninput[%d] = %c", i, input[i]);
	while (input[i])
	{
		if (ft_isspace(input[i]))
		{
			i++;
		}
		else if (input[i] == '\\' && input[i + 1])
		{
			escaped = ft_handle_escaped_char(input, &i);
			ft_add_token(&tokens, ft_new_token(T_WORD, escaped));
		}
		else if ((input[i] == '"' && input[i + 1] == '$') || input[i] == '$')
		{
		//	printf("while input %s e i %d\n\n", input, i);
			i = ft_handle_expander(input, i, shell, &tokens);
		}
		else if (input[i] == '"' || input[i] == '\'')
			i = ft_handle_quoted(input, i, &tokens, input[i]);
		else if (ft_is_operator(input[i]))
			i = ft_handle_token(input, i, &tokens);
		else
		{
		//	printf("handle word input %s, i %d\n\n", input, i);
			i = ft_handle_word(input, i, &tokens);
		}	
	}
	return (tokens);
}
