/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:58:27 by gapachec          #+#    #+#             */
/*   Updated: 2025/07/01 19:03:15 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

int	builtin_export(char **args, t_env **env)
{
	int		i;
	char	*key;
	char	*value;
	char	*eq;

	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		eq = ft_strchr(args[i], '=');
		if (eq)
		{
			*eq = '\0';
			key = args[i];
			value = eq + 1;
			set_env_value(env, key, value);
			*eq = '=';
		}
		i++;
	}
	return (0);
}
