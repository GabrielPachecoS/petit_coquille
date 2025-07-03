/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:58:28 by gapachec          #+#    #+#             */
/*   Updated: 2025/07/01 19:03:20 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

int	builtin_unset(char **args, t_env **env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		unset_env_key(env, args[i]);
		i++;
	}
	return (0);
}
