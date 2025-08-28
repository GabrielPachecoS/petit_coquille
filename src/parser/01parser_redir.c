/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01parser_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:04:01 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/28 17:11:07 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read_heredoc(t_shell *shell, t_command *cmd, int fd)
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
			break ;
		else
		{
			ft_putstr_fd(input, fd);
			write(fd, "\n", 1);
		}
	}
	cmd->redir_in = ft_strdup("heredoc_tmp.txt");
}

static int	ft_redirin_cont(t_shell *shell, t_command *cmd, t_token **tok)
{
	char	*temp;
	int		fd;

	if (cmd->redir_in)
		free(cmd->redir_in);
	if (shell->heredoc)
		free(shell->heredoc);
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
	ft_read_heredoc(shell, cmd, fd);
	close(fd);
	return (1);
}

/*
 * @brief Parses input redirection from tokens and stores it in the command.
 * Advances the token pointer past*tok = 
 * (*tok)->next; the redirection operator and expects
 * a file name token next.
 * @param cmd Pointer to the current command.
 * @param tok Double pointer to the current token; will be advanced.
 * @return 1 if parsing was successful, 0 if syntax error or allocation failed.
 */
int	ft_parser_redir_in(t_shell *shell, t_command *cmd, t_token **tok)
{
	if ((*tok)->type == T_REDIR_IN)
	{
		*tok = (*tok)->next;
		if (!*tok || (*tok)->type != T_WORD)
			return (0);
		if (cmd->redir_in)
			free(cmd->redir_in);
		cmd->redir_in = ft_strdup((*tok)->value);
		return (1);
	}
	else if ((*tok)->type == T_HEREDOC)
		return (ft_redirin_cont(shell, cmd, tok));
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
	if (cmd->redir_out)
		free(cmd->redir_out);
	cmd->redir_out = ft_strdup((*tok)->value);
	return (1);
}
