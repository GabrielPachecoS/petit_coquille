/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:24:58 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/30 13:40:10 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lexer(char *input)
{
	int		i;
	t_token	*tokens;
	char	*escaped;

	i = 0;
	tokens = NULL;
	while (input[i])
	{
		if (input[i] == ' ')
			i++;
		else if (input[i] == '\\' && input[i + 1])
		{
			escaped = ft_handle_escaped_char(input, &i);
			ft_add_token(&tokens, ft_new_token(T_WORD, escaped));
		}
		else if (input[i] == '"' || input[i] == '\'')
			i = ft_handle_quoted(input, i, &tokens, input[i]);
		else if (ft_is_operator(input[i]))
			i = ft_handle_token(input, i, &tokens);
		else
			i = ft_handle_word(input, i, &tokens);
	}
	return (tokens);
}
