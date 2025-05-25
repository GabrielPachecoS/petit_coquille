/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:37:47 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/25 19:02:57 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_signals(void)
{
	signal(SIGINT, SIG_IGN); // Ignora sinal de interrupção (Ctrl+C) para não fechar o shell
	signal(SIGQUIT, SIG_IGN); 	// Ignora sinal de quit (Ctrl+\) também
}
