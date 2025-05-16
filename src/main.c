/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:31:15 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/16 11:05:04 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell; // Estrutura principal do shell (estado do shell)

	// Esses dois (argc e argv) não serão usados, então fazemos "cast" para evitar warnings
	(void)argc;
	(void)argv;

	shell.envp = envp;  // Armazena variáveis de ambiente na struct
	shell.last_exit_status = 0;  // Inicializa status de saída como zero (sem erro)
	handle_signals();  // Configura sinais como Ctrl+C e Ctrl+\ para não quebrar o shell

	// Iniciamos o loop principal do shell
	start_minishell(&shell);

	// Quando o loop encerrar (Ctrl+D), o programa termina
	return (0);
}
