/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:35:31 by gapachec          #+#    #+#             */
/*   Updated: 2025/07/03 21:36:54 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

static int      extract_pair(char *entry, char **out_key, char **out_val)
{
	char	*equal_sign;
	int		len;

	equal_sign = ft_strchr(entry, '=');
	if (equal_sign)
	{
		len = equal_sign - entry;
		*out_key = ft_substr(entry, 0, len);
		*out_val = ft_strdup(equal_sign + 1);
	}
	else
	{
		*out_key = ft_strdup(entry);
		*out_val = NULL;
	}
	if (!*out_key || (equal_sign && !*out_val))
		return (0);
	return (1);
}

static t_env	*env_pair_create(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	if (value)
		env->value = ft_strdup(value);
	else
		env->value = NULL;
	env->next = NULL;
	return (env);
}

static void	env_list_append(t_env **env, t_env *new_node)
{
	t_env	*tmp;

	tmp = *env;
	if (!*env)
	{
		*env = new_node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

t_env	*env_init(char **envp)
{
	t_env	*env;
	t_env	*node;
	char	*key;
	char	*value;

	env = NULL;
	while (*envp)
	{
		if (extract_pair(*envp, &key, &value))
		{
			node = env_pair_create(key, value);
			free(key);
			free(value);
			env_list_append(&env, node);
		}
		envp++;
	}
	return (env);
}
