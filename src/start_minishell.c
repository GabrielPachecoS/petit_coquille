/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:35:26 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/16 11:09:55 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	start_minishell(t_shell *shell)
{
	char	*input;         // Guarda a linha digitada
	t_token	*tokens;        // Lista de tokens após o lexer
	t_command *cmds;        // Lista de comandos após o parser

    (void)shell; // Evita warning caso a struct ainda não seja usada
	while (1)
	{
		// readline mostra o prompt e espera o usuário digitar
		input = readline("minishell$ ");

		// Se o usuário apertar Ctrl+D (EOF), readline retorna NULL
		if (!input)
		{
			// Mostramos "exit" e saímos do shell
			write(1, "exit\n", 5);
			break ;
		}

		// Se o usuário digitou algo, adicionamos ao histórico (seta ↑ depois funciona)
		if (*input)
			add_history(input);

        // Lexer transforma string em tokens
        tokens = lexer(input);
        // Exibe os tokens para debug
        print_tokens(tokens);

        // Parser transforma tokens em comandos encadeados
        cmds = parser(tokens);
        // Exibe comandos para debug
        print_commands(cmds);
        
        // Libera memória das listas temporárias
        free_commands(cmds);
        free_tokens(tokens);

		// Liberamos a memória da linha que foi lida
		cleanup(input);
	}
}
