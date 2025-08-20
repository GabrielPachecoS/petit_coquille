/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:06:19 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/20 00:03:50 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_commands(t_shell *shell, t_command *cmd)
{
	int	i;

	while (cmd)
	{
		i = 0;
		printf("Comando:\n");
		if (cmd->argv)
		{
			while (cmd->argv[i])
			{
				printf(" argv[%d]: %s\n", i, cmd->argv[i]);
				i++;
			}
		}
		while (cmd->redir_in)
		{
			printf(" redir_in[%d]: %s\n", i, cmd->redir_in->value);
			cmd->redir_in = cmd->redir_in->next;	
		}
		while (cmd->redir_out)
		{
			printf("redir_out[%d]: %s\n", i, cmd->redir_out->value);
			cmd->redir_out = cmd->redir_out->next;
		}
		cmd = cmd->next;
		if (shell->infile)
			printf("Shell infile %s\n\n", shell->infile);
	}
}

void	ft_print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: [%d] \"%s\"\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
}
