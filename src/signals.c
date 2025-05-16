/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:37:47 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/16 11:06:29 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_signals(void)
{
	signal(SIGINT, SIG_IGN); // Ignora sinal de interrupção (Ctrl+C) para não fechar o shell
	signal(SIGQUIT, SIG_IGN); 	// Ignora sinal de quit (Ctrl+\) também
}
