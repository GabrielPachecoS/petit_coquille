/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:04:01 by jucoelho          #+#    #+#             */
/*   Updated: 2025/07/05 22:41:59 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees all commands in the linked list, including their argv arrays
 *        and redirection strings.
 *
 * @param cmd Pointer to the head of the command list.
 */
void	ft_free_commands(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	i = 0;
	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->argv)
		{
			while (cmd->argv[i])
				free(cmd->argv[i++]);
			free(cmd->argv);
		}
		free(cmd);
		cmd = tmp;
	}
}

/**
 * @brief Handles input redirection parsing.
 *
 * Sets the shell's input redirection type and stores the name of the
 * input file found in the next token. Expects a T_WORD token after
 * the redirection symbol.
 *
 * @param shell Pointer to the shell structure.
 * @param tok Pointer to the current token pointer.
 *
 * @return 1 on success, 0 if the expected filename token is missing.
 */
int	ft_parser_redir_in(t_shell *shell, t_token **tok)
{
	shell->fd_in = (*tok)->type;
	*tok = (*tok)->next;
	if (!*tok || (*tok)->type != T_WORD)
		return (0);
	shell->infile = ft_strdup((*tok)->value);
	return (1);
}

/**
 * @brief Handles output redirection parsing.
 *
 * Sets the shell's output redirection type and stores the name of the
 * output file found in the next token. Expects a T_WORD token after
 * the redirection symbol.
 *
 * @param shell Pointer to the shell structure.
 * @param tok Pointer to the current token pointer.
 *
 * @return 1 on success, 0 if the expected filename token is missing.
 */

int	ft_parser_redir_out(t_shell *shell, t_token **tok)
{
	shell->fd_out = (*tok)->type;
	*tok = (*tok)->next;
	if (!*tok || (*tok)->type != T_WORD)
		return (0);
	shell->outfile = ft_strdup((*tok)->value);
	return (1);
}

/**
 * @brief Handles pipe token by creating a new command node.
 *
 * Allocates a new command structure and links it to the current command,
 * updating the command pointer to point to the newly created node.
 *
 * @param cmd Pointer to the current command pointer.
 *
 * @return 1 on success, 0 on allocation failure.
 */
int	ft_parser_pipe(t_command **cmd)
{
	(*cmd)->next = ft_new_command();
	if (!(*cmd)->next)
		return (0);
	*cmd = (*cmd)->next;
	return (1);
}
