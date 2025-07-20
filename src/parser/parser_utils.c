/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:04:01 by jucoelho          #+#    #+#             */
/*   Updated: 2025/07/19 22:44:57 by jucoelho         ###   ########.fr       */
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
 * @brief Parses input redirection from tokens and stores it in the command.
 *
 * Advances the token pointer past the redirection operator and expects
 * a file name token next.
 *
 * @param cmd Pointer to the current command.
 * @param tok Double pointer to the current token; will be advanced.
 *
 * @return 1 if parsing was successful, 0 if syntax error or allocation failed.
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
 * @brief Parses output redirection from tokens and stores it in the command.
 *
 * Advances the token pointer past the redirection operator and expects
 * a file name token next.
 *
 * @param cmd Pointer to the current command.
 * @param tok Double pointer to the current token; will be advanced.
 *
 * @return 1 if parsing was successful, 0 if syntax error or allocation failed.
 */
int	ft_parser_redir_out(t_shell *shell, t_token **tok)
{
	if ((*tok)->type == T_REDIR_APPEND)
		shell->append = 1;
	shell->fd_out = (*tok)->type;
	*tok = (*tok)->next;
	if (!*tok || (*tok)->type != T_WORD)
		return (0);
	shell->outfile = ft_strdup((*tok)->value);
	return (1);
}

/**
 * @brief Handles pipe token by creating a new command linked to the current one.
 *
 * Sets the next pointer of the current command to a newly allocated command,
 * then updates the current pointer to this new command.
 *
 * @param cmd Double pointer to the current command; will be updated.
 *
 * @return 1 if successful, 0 if memory allocation failed.
 */
int	ft_parser_pipe(t_command **cmd)
{
	(*cmd)->next = ft_new_command();
	if (!(*cmd)->next)
		return (0);
	*cmd = (*cmd)->next;
	return (1);
}
