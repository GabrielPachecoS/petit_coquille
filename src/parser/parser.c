/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:14:17 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/16 11:21:34 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Cria novo comando vazio
static t_command	*new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));  // Aloca espaço para um comando
	if (!cmd)
		return (NULL);

	// Inicializa todos os campos com valores neutros
	cmd->argv = NULL;
	cmd->redir_in = 0;
	cmd->redir_in_file = NULL;
	cmd->redir_out = 0;
	cmd->redir_out_file = NULL;
	cmd->next = NULL;

	return (cmd);  // Retorna comando vazio
}

// Adiciona string ao argv (realloc + NULL terminator)
static int	add_argv(t_command *cmd, char *arg)
{
	char	**new_argv;
	int		count = 0;

	if (!cmd)
		return (0);

	// Conta quantos argumentos já existem
	if (cmd->argv)
	{
		while (cmd->argv[count])
			count++;
	}
	new_argv = malloc(sizeof(char *) * (count + 2)); // Novo array com +1 slot e NULL final
	if (!new_argv)
		return (0);

	// Copia argumentos antigos para novo array
	for (int i = 0; i < count; i++)
		new_argv[i] = cmd->argv[i];

	// Adiciona novo argumento e NULL termina
	new_argv[count] = strdup(arg);
	new_argv[count + 1] = NULL;

	free(cmd->argv);         // Libera array antigo
	cmd->argv = new_argv;    // Substitui pelo novo
	return (1);
}

t_command	*parser(t_token *tokens)
{
	t_command	*head = NULL;  // Primeiro comando
	t_command	*curr = NULL;  // Comando atual sendo preenchido
	t_token		*tok = tokens; // Iterador de tokens

	while (tok)
	{
		// Se não temos um comando atual, criamos um novo
		if (!curr)
		{
			curr = new_command();
			if (!curr)
				return (NULL);
			head = curr;  // Armazenamos o primeiro da lista
		}
		if (tok->type == T_WORD)
		{
			if (!add_argv(curr, tok->value))
				return (NULL);
		}
		else if (tok->type == T_PIPE)
		{
			curr->next = new_command();
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

			curr->redir_in_file = strdup(tok->value);
		}
		else if (tok->type == T_REDIR_OUT || tok->type == T_REDIR_APPEND)
		{
			curr->redir_out = tok->type;
			tok = tok->next;
			if (!tok || tok->type != T_WORD)
				return (NULL); // erro sintático simples
			curr->redir_out_file = strdup(tok->value);
		}
		tok = tok->next;  // Avança para o próximo token
	}
	return (head);  // Retorna a lista encadeada de comandos
}

// Função para liberar a lista de comandos
void	free_commands(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	while (cmd)
	{
		tmp = cmd->next;

		// Libera argumentos
		if (cmd->argv)
		{
			for (i = 0; cmd->argv[i]; i++)
				free(cmd->argv[i]);
			free(cmd->argv);
		}

		// Libera arquivos de redirecionamento, se existirem
		if (cmd->redir_in_file)
			free(cmd->redir_in_file);
		if (cmd->redir_out_file)
			free(cmd->redir_out_file);
			
		free(cmd);  // Libera comando atual
		cmd = tmp;
	}
}

//função para printar os comandos reconstruidos pelo parser
void	print_commands(t_command *cmd)
{
	int	i;

	while (cmd)
	{
		printf("Comando:\n");
		if (cmd->argv)
		{
			for (i = 0; cmd->argv[i]; i++)
				printf(" argv[%d]: %s\n", i, cmd->argv[i]);
		}
		if (cmd->redir_in)
			printf(" Redir entrada: %s\n", cmd->redir_in_file);
		if (cmd->redir_out)
			printf(" Redir saída: %s\n", cmd->redir_out_file);
		cmd = cmd->next;
	}
}
