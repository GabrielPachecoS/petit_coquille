/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:28:27 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/28 15:05:13 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Retrieves the value of an environment variable by key.
 *   - Searches the linked list for a matching key
 *   - Returns the value if found, or NULL if not found
 */
char	*env_var(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

t_env	*env_lookup(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

/*
 * Updates the value of an existing environment variable node.
 *   - If has_value is true, replaces the old value with the new one
 *   - If has_value is false, frees the unused value string
 */
static void	update_existing_env(t_env *node, char *value, int has_value)
{
	if (has_value)
	{
		free(node->value);
		node->value = value;
	}
	else
		free(value);
}

/*
 * Updates an existing environment variable or adds a new one.
 *   - If key exists in the list, updates its value (if provided)
 *   - If key doesn't exist, creates and appends a new node
 *   - Frees key and value appropriately in both cases
 *   - Returns 0 on success, 1 on allocation failure or invalid input
 */
int	update_or_add_env(t_env **env, char *key, char *value,
	int has_value)
{
	t_env	*node;
	t_env	*new_node;

	if (has_value && !value)
	{
		free(key);
		return (1);
	}
	node = env_lookup(*env, key);
	if (node)
	{
		update_existing_env(node, value, has_value);
		free(key);
	}
	else
	{
		new_node = env_pair_create(key, value);
		free(key);
		free(value);
		if (!new_node)
			return (1);
		env_list_append(env, new_node);
	}
	return (0);
}
