/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:14:17 by gapachec          #+#    #+#             */
/*   Updated: 2025/08/14 16:40:33 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates a new empty command structure.
 *
 * Allocates and initializes a new t_command struct with default values.
 *
 * @return Pointer to the newly created command, or NULL if allocation fails.
 */
t_command	*ft_new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->next = NULL;
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	return (cmd);
}

/**
 * @brief Adds a string argument to the command's argv array.
 *
 * Reallocates the argv array to accommodate the new argument, duplicates
 * the argument string, and appends it with a NULL terminator.
 *
 * @param cmd Pointer to the command structure.
 * @param arg The argument string to add.
 *
 * @return 1 if successful, 0 on failure (e.g., memory allocation error).
 */
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
		new_argv[i] = ft_strdup(cmd->argv[i]);
		free(cmd->argv[i]);
		i++;
	}
	new_argv[count] = ft_strdup(arg);
	new_argv[count + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
	return (1);
}

/**
 * @brief Initializes the first command in the list.
 *
 * Creates a new command and sets it as both the current and head command.
 *
 * @param curr Double pointer to the current command (to be initialized).
 * @param head Double pointer to the head of the command list.
 *
 * @return 1 if successful, 0 if memory allocation failed.
 */
static int	ft_parser_start(t_command **curr, t_command **head)
{
	*curr = ft_new_command();
	if (!*curr)
		return (0);
	*head = *curr;
	return (1);
}

/**
 * @brief Dispatches the current token to the appropriate handler,
 *        updating the current command accordingly.
 *
 * - If the token is a word, it adds it to the argv array of the current
 *   command.
 * - If the token is a pipe, it creates a new command and switches the
 *   current pointer to it.
 * - If the token is an input redirection or heredoc, it calls the input
 *   redirection handler.
 * - If the token is an output redirection (either overwrite or append),
 *   it calls the output redirection handler.
 *
 * @param curr Pointer to the current command pointer (which may be updated
 *             in case of pipe).
 * @param tok Pointer to the current token pointer (may be advanced by
 *            redirection handlers).
 *
 * @return Returns 1 on success, or 0 on failure.
 */
static int	ft_parser_dispatch(t_command **curr, t_token **tok, t_shell *shell)
{
	if ((*tok)->type == T_WORD)
		return (ft_add_argv(*curr, (*tok)->value));
	else if ((*tok)->type == T_PIPE)
		return (ft_parser_pipe(curr));
	else if ((*tok)->type == T_REDIR_IN || (*tok)->type == T_HEREDOC)
		return (ft_parser_redir_in(shell, *curr, tok));
	else if ((*tok)->type == T_REDIR_OUT || (*tok)->type == T_REDIR_APPEND)
		return (ft_parser_redir_out(shell, *curr, tok));
	return (1);
}

/**
 * @brief Parses a linked list of tokens into a linked list of commands.
 *
 * Iterates over the tokens list, creating new commands on encountering
 * pipes, and builds the argv and redirection fields for each command.
 *
 * @param tokens Pointer to the first token in the token list.
 *
 * @return Pointer to the head of the linked list of commands, or NULL on
 *         failure.
 */
t_command	*ft_parser(t_token *tokens, t_shell *shell)
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
		if (!ft_parser_dispatch(&curr, &tok, shell))
			return (NULL);
		tok = tok->next;
	}
	return (head);
}
