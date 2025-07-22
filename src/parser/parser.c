/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:14:17 by gapachec          #+#    #+#             */
/*   Updated: 2025/07/16 18:30:17 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Allocates and initializes a new command structure.
 *
 * Creates a new t_command node with argv set to NULL and next set to NULL.
 *
 * @return Pointer to the newly allocated command structure, or NULL on failure.
 */
t_command	*ft_new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->next = NULL;
	return (cmd);
}

/**
 * @brief Adds an argument to the argv list of a command.
 *
 * Expands the current argv array of the command and appends a new string
 * to it, duplicating the input argument. Handles dynamic allocation and
 * ensures NULL-termination of the array.
 *
 * @param cmd Pointer to the command structure.
 * @param arg Argument string to be added.
 *
 * @return 1 on success, 0 on allocation failure or if cmd is NULL.
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
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[count] = ft_strdup(arg);
	new_argv[count + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
	return (1);
}

/**
 * @brief Initializes the parser by creating the first command node.
 *
 * Allocates a new command and assigns it to both the current and head
 * pointers of the command list.
 *
 * @param curr Pointer to the current command pointer.
 * @param head Pointer to the head of the command list.
 *
 * @return 1 on success, 0 on allocation failure.
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
 * @brief Dispatches token processing to the appropriate parser function.
 *
 * Analyzes the current token type and updates the command structure accordingly,
 * handling arguments, pipes, and input/output redirections.
 *
 * @param curr Pointer to the current command node.
 * @param tok Pointer to the current token pointer.
 * @param shell Shell context used for redirection processing.
 *
 * @return 1 on success, 0 on failure.
 */
static int	ft_parser_dispatch(t_command **curr, t_token **tok, t_shell shell)
{
	if ((*tok)->type == T_WORD)
		return (ft_add_argv(*curr, (*tok)->value));
	else if ((*tok)->type == T_PIPE)
		return (ft_parser_pipe(curr));
	else if ((*tok)->type == T_REDIR_IN || (*tok)->type == T_HEREDOC)
		return (ft_parser_redir_in(&shell, tok));
	else if ((*tok)->type == T_REDIR_OUT || (*tok)->type == T_REDIR_APPEND)
		return (ft_parser_redir_out(&shell, tok));
	return (1);
}

/**
 * @brief Parses a list of tokens into a list of commands.
 *
 * This function iterates over the list of tokens and constructs a
 * linked list of command structures. A new command node is created
 * whenever a pipe token is encountered. For each command, it builds
 * the argument vector (argv) and sets up input/output redirections
 * accordingly.
 *
 * @param tokens Pointer to the first token in the token list.
 * @param shell  Shell context containing environment and status.
 *
 * @return Pointer to the head of the command list, or NULL on failure.
 */
t_command	*ft_parser(t_token *tokens, t_shell shell)
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
