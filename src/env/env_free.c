/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:31:15 by gapachec          #+#    #+#             */
/*   Updated: 2025/07/15 15:36:00 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

void	env_node_destroy(t_env *env)
{
	if (!env)
		return ;
	free(env->key);
	free(env->value);
	free(env);
}

void	env_destroy(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		env_node_destroy(env);
		env = tmp;
	}
}
