/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:35:26 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/16 09:43:49 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	start_minishell(t_shell *shell)
{
	char	*input;

    (void)shell;
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

		// Aqui, futuramente, vamos chamar o lexer, parser e executor
		// Exemplo: tokenize_and_execute(input, shell);

		// Liberamos a memória da linha que foi lida
		cleanup(input);
	}
}
