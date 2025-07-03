/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:06:23 by gapachec          #+#    #+#             */
/*   Updated: 2025/07/01 19:59:25 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

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

	count = ft_lstsize(env);
	tmp = env;
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
