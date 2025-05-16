/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:37:21 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/16 09:37:32 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cleanup(char *input)
{
	// Essa função simplesmente dá free na string digitada pelo usuário
	// Sempre chamamos ela no fim do loop para evitar vazamentos de memória
	free(input);
}
