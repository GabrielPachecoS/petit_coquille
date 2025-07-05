/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:06:23 by gapachec          #+#    #+#             */
/*   Updated: 2025/07/04 19:06:50 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

int env_size(t_env *env)
{
	int count = 0;

	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static char	*join_env_var(char *key, char *value)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, value);
	free(temp);
	return (result);
}

char	**env_to_array(t_env *env)
{
	char	**array;
	t_env	*tmp;
	int		count;
	int		i;

	tmp = env;
	count = env_size(env);
	i = 0;
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	while (tmp)
	{
		if (tmp->value)
			array[i++] = join_env_var(tmp->key, tmp->value);
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}
