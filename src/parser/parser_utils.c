/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:04:01 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/19 17:50:57 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @brief Frees all commands in the linked list, including their argv arrays
 *        and redirection strings.
 *
 * @param cmd Pointer to the head of the command list.
 */
void	ft_free_commands(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	while (cmd)
	{
		i = 0;
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

void	ft_read_heredoc(t_shell *shell, int fd)
{
	char	*input;

	while (1)
	{
		input = readline("heredoc> ");
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (ft_strcmp(input, shell->heredoc) == 0)
		{
			break ;
		}
		else
		{
			ft_putstr_fd(input, fd);
			write(fd, "\n", 1);
		}
	}
	shell->infile = ft_strdup("heredoc_tmp.txt");
}

/*
 * @brief Parses input redirection from tokens and stores it in the command.
 * Advances the token pointer past*tok = (*tok)->next; the redirection operator and expects
 * a file name token next.
 * @param cmd Pointer to the current command.
 * @param tok Double pointer to the current token; will be advanced.
 * @return 1 if parsing was successful, 0 if syntax error or allocation failed.
 */
int	ft_parser_redir_in(t_shell *shell, t_command *cmd, t_token **tok)
{
	char	*temp;
	int		fd;

	if ((*tok)->type == T_REDIR_IN)
	{
		*tok = (*tok)->next;
		if (!*tok || (*tok)->type != T_WORD)
			return (0);
		cmd->redir_in = ft_strdup((*tok)->value);
	}
	else if ((*tok)->type == T_HEREDOC)
	{
		temp = "heredoc_tmp.txt";
		*tok = (*tok)->next;
		if (!*tok || (*tok)->type != T_WORD)
			return (0);
		shell->heredoc = ft_strdup((*tok)->value);
		fd = open(temp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(temp);
			shell->status = 1;
			return (0);
		}
		ft_read_heredoc(shell, fd);
		close(fd);
	}
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
int	ft_parser_redir_out(t_shell *shell, t_command *cmd, t_token **tok)
{
	if ((*tok)->type == T_REDIR_APPEND)
		shell->append = 1;
	*tok = (*tok)->next;
	if (!*tok || (*tok)->type != T_WORD)
		return (0);
	cmd->redir_out = ft_strdup((*tok)->value);
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
