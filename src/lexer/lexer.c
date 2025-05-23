/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:24:58 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/23 16:24:50 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/token.h"

static t_token	*ft_new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

static void	ft_add_token(t_token **list, t_token *new)
{
	t_token	*cur;

	if (!*list)
	{
		*list = new;
		return ;
	}
	cur = *list;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

int	ft_handle_token(char *input, int i, t_token **tokens)
{
	if (input[i] == '|')
	{
		ft_add_token(tokens, ft_new_token(T_PIPE, ft_substr(input, i, i + 1)));
		return (i + 1);
	}
	if (input[i] == '>' && input[i + 1] == '>')
	{
		ft_add_token(tokens, ft_new_token(T_REDIR_APPEND, ft_substr(input, i, i + 2)));
		return (i + 2);
	}
	if (input[i] == '<' && input[i + 1] == '<')
	{
		ft_add_token(tokens, ft_new_token(T_HEREDOC, ft_substr(input, i, i + 2)));
		return (i + 2);
	}
	if (input[i] == '>')
	{
		ft_add_token(tokens, ft_new_token(T_REDIR_OUT, ft_substr(input, i, i + 1)));
		return (i + 1);
	}
	if (input[i] == '<')
	{
		ft_add_token(tokens, ft_new_token(T_REDIR_IN, ft_substr(input, i, i + 1)));
		return (i + 1);
	}
}

t_token	*ft_lexer(char *input)
{
	int		i;
	int		start;
	t_token	*tokens;

	i = 0;
	tokens = NULL;
	while (input[i])
	{
		if (input[i] == ' ')
			i++;
		else if (input[i] == '<' || input[i] == '>' || input[i] == '|')
			i = ft_handle_token(input, i, &tokens);
		else
		{
			start = i;
			while (input[i] && input[i] != ' ' && input[i] != '|' && input[i] != '<' && input[i] != '>')
				i++;
			ft_add_token(tokens, ft_new_token(T_WORD, ft_substr(input, start, i)));
		}
	}
	return (tokens);
}
