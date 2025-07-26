/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:58:28 by gapachec          #+#    #+#             */
/*   Updated: 2025/07/25 23:24:31 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

/*
 * Removes an environment variable from the list.
 *   - Searches for a node with key equal to `arg`
 *   - Frees the node and adjusts pointers accordingly
 *   - Returns 0 if found and removed, 1 otherwise
 */
static int	unset_one(char *arg, t_env **env)
{
	t_env	*prev;
	t_env	*curr;

	prev = NULL;
	curr = *env;
	while (curr)
	{
		if (ft_strcmp(curr->key, arg) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			env_node_destroy(curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (1);
}

/*
 * Implements the 'unset' builtin.
 *   - Iterates over all arguments and removes each variable
 *   - Does not fail on invalid keys (silent by design)
 */
int	builtin_unset(char **argv, t_env **env)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		unset_one(argv[i], env);
		i++;
	}
	return (0);
}