/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:49:27 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/15 21:37:59 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

??	ft_expander(shell, cmds, tokens)
{
	//verifica se tem aspas simples no argv, infile e outfile
	//se tem retira aspas simples e substitui o comando
	ft_is_squoted(cmds, '\'')
	//verifica se tem aspas duplas no argv
	//se sim verifica se tem expander e trata o expander
	if(ft_is_dquoted(cmds, '"'))
		\\return aqui
	//verifica se tem expander sem aspas e trata o expander
	else
		 ft_handle_expander(input, i, shell, &tokens);
}
