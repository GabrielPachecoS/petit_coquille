/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:14:17 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/25 19:02:45 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Cria novo comando vazio
static t_command	*ft_new_command(void)
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
	int		count = 0;

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
	for (int i = 0; i < count; i++)
		new_argv[i] = cmd->argv[i];
	new_argv[count] = ft_strdup(arg);
	new_argv[count + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
	return (1);
}

t_command	*ft_parser(t_token *tokens)
{
	t_command	*head = NULL;  // Primeiro comando
	t_command	*curr = NULL;  // Comando atual sendo preenchido
	t_token		*tok = tokens; // Iterador de tokens

	while (tok)
	{
		if (!curr)
		{
			curr = ft_new_command();
			if (!curr)
				return (NULL);
			head = curr;
		}
		if (tok->type == T_WORD)
		{
			if (!ft_add_argv(curr, tok->value))
				return (NULL);
		}
		else if (tok->type == T_PIPE)
		{
			curr->next = ft_new_command();
			if (!curr->next)
				return (NULL);
			curr = curr->next;  // Passa a preencher o próximo
		}
		else if (tok->type == T_REDIR_IN || tok->type == T_HEREDOC)
		{
			curr->redir_in = tok->type;  // Marca tipo de redirecionamento
			tok = tok->next;             // Espera próximo token ser o nome do arquivo

			if (!tok || tok->type != T_WORD)
				return (NULL);           // Erro sintático (arquivo ausente)

			curr->redir_in_file = ft_strdup(tok->value);
		}
		else if (tok->type == T_REDIR_OUT || tok->type == T_REDIR_APPEND)
		{
			curr->redir_out = tok->type;
			tok = tok->next;
			if (!tok || tok->type != T_WORD)
				return (NULL); // erro sintático simples
			curr->redir_out_file = ft_strdup(tok->value);
		}
		tok = tok->next;  // Avança para o próximo token
	}
	return (head);  // Retorna a lista encadeada de comandos
}
