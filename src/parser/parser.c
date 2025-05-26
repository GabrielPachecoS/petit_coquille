/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:14:17 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/25 23:28:31 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Cria novo comando vazio
t_command	*ft_new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redir_in = 0;
	cmd->redir_in_file = NULL;
	cmd->redir_out = 0;
	cmd->redir_out_file = NULL;
	cmd->next = NULL;
	return (cmd);
}

// Adiciona string ao argv (realloc + NULL terminator)
static int	ft_add_argv(t_command *cmd, char *arg)
{
	char	**new_argv;
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (!cmd)
		return (0);
	if (cmd->argv)
	{
		while (cmd->argv[count])
			count++;
	}
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		return (0);
	while (i < count)
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[count] = ft_strdup(arg);
	new_argv[count + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
	return (1);
}

static int	ft_parser_start(t_command **curr, t_command **head)
{
	*curr = ft_new_command();
	if (!*curr)
		return (0);
	*head = *curr;
	return (1);
}

static int	ft_parser_dispatch(t_command **curr, t_token **tok)
{
	if ((*tok)->type == T_WORD)
		return (ft_add_argv(*curr, (*tok)->value));
	else if ((*tok)->type == T_PIPE)	
		return (ft_parser_pipe(curr));
	else if ((*tok)->type == T_REDIR_IN || (*tok)->type == T_HEREDOC)
		return (ft_parser_redir_in(*curr, tok));
	else if ((*tok)->type == T_REDIR_OUT || (*tok)->type == T_REDIR_APPEND)
		return (ft_parser_redir_out(*curr, tok));
	return (1);
}

t_command	*ft_parser(t_token *tokens)
{
	t_command	*head;
	t_command	*curr;
	t_token		*tok;

	head = NULL;
	curr = NULL;
	tok = tokens;
	while (tok)
	{
		if (!curr)
		{
			if (!ft_parser_start(&curr, &head))
				return (NULL);
		}
		if (!ft_parser_dispatch(&curr, &tok))
			return (NULL);
		tok = tok->next;
	}
	return (head);
}
