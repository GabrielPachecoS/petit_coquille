/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:31:15 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/16 09:43:11 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	// Esses dois (argc e argv) não serão usados, então fazemos "cast" para evitar warnings
	(void)argc;
	(void)argv;

	// Guardamos o ambiente original (envp) dentro da struct principal do shell
	shell.envp = envp;

	// Inicializamos o status de saída do último comando como 0
	shell.last_exit_status = 0;

	// Chamamos função para lidar com sinais como Ctrl+C e Ctrl+
	handle_signals();

	// Iniciamos o loop principal do shell
	start_minishell(&shell);

	// Quando o loop encerrar (Ctrl+D), o programa termina
	return (0);
}
