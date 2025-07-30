/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:58:34 by gapachec          #+#    #+#             */
/*   Updated: 2025/07/30 16:02:39 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "builtin.h"

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_builtin_exit(char **args, t_shell *shell)
{
	int	code;

	if (args[1] && args[2])
	{
		write(2, " too many arguments\n", 20);
		shell->last_exit_status = 1;
		return (0);
	}
	if (args[1] && !is_numeric(args[1]))
	{
		write(2, " numeric argument required\n", 27);
		shell->should_exit = 1;
		shell->exit_code = 2;
		return (1);
	}
	if (args[1])
		code = ft_atol(args[1]);
	else
		code = shell->last_exit_status;
	shell->should_exit = 1;
	shell->exit_code = (unsigned char)code;
	return (1);
}