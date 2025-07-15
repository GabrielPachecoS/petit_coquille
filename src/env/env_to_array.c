/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:06:23 by gapachec          #+#    #+#             */
/*   Updated: 2025/07/15 15:39:49 by jucoelho         ###   ########.fr       */
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

	count = ft_lstsize_env(env);
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
int	ft_lstsize_env(t_env *env)
{
	int	nbr_nodes;

	nbr_nodes = 0;
	while (env)
	{
		env = env->next;
		nbr_nodes++;
	}
	return (nbr_nodes);
}
