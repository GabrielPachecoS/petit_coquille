/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:37:47 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/16 09:38:02 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_signals(void)
{
	// Por enquanto, vamos apenas ignorar Ctrl+C e Ctrl+\ para evitar que quebrem o shell
	// Depois podemos fazer uma função que trata SIGINT e mostra um prompt novo, por exemplo
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
