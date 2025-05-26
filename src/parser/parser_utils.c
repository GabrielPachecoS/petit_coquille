/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:04:01 by jucoelho          #+#    #+#             */
/*   Updated: 2025/05/25 23:30:40 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (cmd->redir_in_file)
			free(cmd->redir_in_file);
		if (cmd->redir_out_file)
			free(cmd->redir_out_file);
		free(cmd);
		cmd = tmp;
	}
}

int	ft_parser_redir_in(t_command *cmd, t_token **tok)
{
	cmd->redir_in = (*tok)->type;
	*tok = (*tok)->next;
	if (!*tok || (*tok)->type != T_WORD)
		return (0);
	cmd->redir_in_file = ft_strdup((*tok)->value);
	return (1);
}

int	ft_parser_redir_out(t_command *cmd, t_token **tok)
{
	cmd->redir_out = (*tok)->type;
	*tok = (*tok)->next;
	if (!*tok || (*tok)->type != T_WORD)
		return (0);
	cmd->redir_out_file = ft_strdup((*tok)->value);
	return (1);
}

int	ft_parser_pipe(t_command **cmd)
{
	(*cmd)->next = ft_new_command();
	if (!(*cmd)->next)
		return (0);
	*cmd = (*cmd)->next;
	return (1);
}

void	ft_print_commands(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		printf("Comando:\n");
		if (cmd->argv)
		{
			while (cmd->argv[i])
			{
				printf(" argv[%d]: %s\n", i, cmd->argv[i]);
				i++;
			}
		}
		if (cmd->redir_in)
			printf(" Redir entrada: %s\n", cmd->redir_in_file);
		if (cmd->redir_out)
			printf(" Redir saída: %s\n", cmd->redir_out_file);
		cmd = cmd->next;
	}
}
