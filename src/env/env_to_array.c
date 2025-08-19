/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:06:23 by gapachec          #+#    #+#             */
/*   Updated: 2025/08/19 17:44:34 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

int	env_size(t_env *env)
{
	int	count;

	count = 0;
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

void	free_env_array(char **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static int	fill_env_array(t_env *env, char **array)
{
	int		i;
	char	*joined;

	i = 0;
	while (env)
	{
		if (env->value)
		{
			joined = join_env_var(env->key, env->value);
			if (!joined)
			{
				free_env_array(array, i);
				return (0);
			}
			array[i++] = joined;
		}
		env = env->next;
	}
	array[i] = NULL;
	return (1);
}

char	**env_to_array(t_env *env)
{
	char	**array;
	int		count;

	count = env_size(env);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	if (!fill_env_array(env, array))
		return (NULL);
	return (array);
}
