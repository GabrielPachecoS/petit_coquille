/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lookup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:31:28 by gapachec          #+#    #+#             */
/*   Updated: 2025/07/04 01:15:39 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

char	*env_lookup(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, 5) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
