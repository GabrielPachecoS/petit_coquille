/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:37:21 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/25 19:02:47 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cleanup(char *input)
{
	// Essa função simplesmente dá free na string digitada pelo usuário (lida com readline())
	// Sempre chamamos ela no fim do loop para evitar vazamentos de memória
	free(input);
}
