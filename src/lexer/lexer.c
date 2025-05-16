/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:24:58 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/16 11:15:38 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/token.h"

/*
 * new_token:
 * Cria um novo token com o tipo e valor fornecidos.
 * Aloca memória para o token e inicializa seus campos.
 * Retorna o ponteiro para o token criado ou NULL em caso de falha.
 */
static t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));  // Aloca espaço para um token
	if (!token)
		return (NULL);
	token->type = type;     // Define o tipo do token (ex: T_WORD, T_PIPE)
	token->value = value;   // Armazena a string (já alocada por substr)
	token->next = NULL;     // Inicializa ponteiro para próximo como NULL
	return (token);         // Retorna o novo token
}

/*
 * add_token:
 * Adiciona o token 'new' no final da lista ligada 'list'.
 * Se a lista estiver vazia, o novo token passa a ser o primeiro.
 */
static void	add_token(t_token **list, t_token *new)
{
	t_token	*cur;

	if (!*list)
	{
		*list = new;  // Se a lista estiver vazia, esse é o primeiro token
		return ;
	}
	cur = *list;
	while (cur->next)
		cur = cur->next;  // Anda até o último
	cur->next = new;     // Adiciona o novo token ao final
}

/*
 * substr:
 * Cria uma nova string que é uma substring de 'str' do índice start até end-1.
 * Aloca memória para a substring.
 * Retorna a substring alocada ou NULL em caso de erro.
 */
static char	*substr(char *str, int start, int end)
{
	char	*sub;
	int		i;

	sub = malloc(end - start + 1);  // Aloca espaço para substring + '\0'
	if (!sub)
		return (NULL);
	i = 0;
	while (start < end)
		sub[i++] = str[start++];  // Copia caracteres para a nova string
	sub[i] = '\0';               // Termina com null
	return (sub);                // Retorna a nova string
}

t_token	*lexer(char *input)
{
	int		i;
	int		start;
	t_token	*tokens;

	i = 0;
	tokens = NULL;
	while (input[i])
	{
		// Ignora espaços entre palavras
		if (input[i] == ' ')
		{
			i++;
			continue ;
		}
		// Se encontrar pipe '|', cria token pipe e avança uma posição
		else if (input[i] == '|')
		{
			add_token(&tokens, new_token(T_PIPE, substr(input, i, i + 1)));
			i++;
		}
		// Se encontrar '>>' (append), cria token e avança duas posições
		else if (input[i] == '>' && input[i + 1] == '>')
		{
			add_token(&tokens, new_token(T_REDIR_APPEND, substr(input, i, i + 2)));
			i += 2;
		}
		// Se encontrar '<<' (heredoc), cria token e avança duas posições
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			add_token(&tokens, new_token(T_HEREDOC, substr(input, i, i + 2)));
			i += 2;
		}
		// Se encontrar '>' (redirecionador de saída), cria token e avança uma posição
		else if (input[i] == '>')
		{
			add_token(&tokens, new_token(T_REDIR_OUT, substr(input, i, i + 1)));
			i++;
		}
		// Se encontrar '<' (redirecionador de entrada), cria token e avança uma posição
		else if (input[i] == '<')
		{
			add_token(&tokens, new_token(T_REDIR_IN, substr(input, i, i + 1)));
			i++;
		}
		// Caso contrário, é uma palavra (comando ou argumento)
		else
		{
			start = i;
			// Continua até encontrar espaço ou algum símbolo especial
			while (input[i] && input[i] != ' ' && input[i] != '|' &&
					input[i] != '<' && input[i] != '>')
				i++;
			// Cria token palavra com substring identificada
			add_token(&tokens, new_token(T_WORD, substr(input, start, i)));
		}
	}
	return (tokens);
}
