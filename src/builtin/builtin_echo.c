/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:58:23 by gapachec          #+#    #+#             */
/*   Updated: 2025/07/16 16:35:42 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

int	builtin_echo(t_shell *shell, char **args)
{
	int		n_flag;
	int		i;

	n_flag = 0;
	i = 1;
	if (args[1] && args[1][0] == '-' && args[1][1] == 'n' && args[1][2] == '\0')
	{
		n_flag = 1;
		i++;
	}
	//funciona só para echo, é só para testar saída
	if (ft_strcmp(args[i], "$?") == 0)
	{
		printf("%d", shell->status);
	}
	else
		while (args[i])
		{
			printf("%s", args[i]);
			if (args[i + 1])
				printf(" ");
			i++;
		}
	if (!n_flag)
		printf("\n");
	return (0);
}
