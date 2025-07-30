/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:27:18 by jucoelho          #+#    #+#             */
/*   Updated: 2025/07/30 15:27:25 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Formats an environment variable node as an export string.
 *   - Starts with "declare -x "
 *   - Adds the key
 *   - If the value exists, appends it as ="value"
 *   - Returns the formatted string, or NULL on failure
 */
static char	*format_export_string(t_env *node)
{
	char	*str;
	int		len;

	if (!node || !node->key)
		return (NULL);
	len = ft_strlen("declare -x ") + ft_strlen(node->key) + 1;
	if (node->value)
		len += ft_strlen("=\"") + ft_strlen(node->value) + 1;
	str = malloc(len);
	if (!str)
		return (NULL);
	ft_strcpy(str, "declare -x ");
	ft_strcat(str, node->key);
	if (node->value)
	{
		ft_strcat(str, "=\"");
		ft_strcat(str, node->value);
		ft_strcat(str, "\"");
	}
	return (str);
}

/*
 * Fills an array with formatted export strings from the environment list.
 *   - Allocates strings using format_export_string
 *   - Returns 1 on success, 0 on allocation failure
 * 											(and frees allocated strings)
 */
static int	fill_env_array(char **env_array, t_env *env)
{
	int		i;
	t_env	*curr;

	i = 0;
	curr = env;
	while (curr)
	{
		env_array[i] = format_export_string(curr);
		if (!env_array[i])
		{
			while (--i >= 0)
				free(env_array[i]);
			return (0);
		}
		i++;
		curr = curr->next;
	}
	env_array[i] = NULL;
	return (1);
}

/*
 * Sorts an array of strings in-place using insertion sort.
 *   - Compares strings lexicographically using ft_strcmp
 *   - Maintains stable order for equal elements
 */
static void	insertion_sort(char **env_array, int size)
{
	int		i;
	int		j;
	char	*key;

	i = 1;
	while (i < size)
	{
		key = env_array[i];
		j = i - 1;
		while (j >= 0 && ft_strcmp(env_array[j], key) > 0)
		{
			env_array[j + 1] = env_array[j];
			j--;
		}
		env_array[j + 1] = key;
		i++;
	}
}

/*
 * Prints each string in the environment array on a new line.
 *   - Assumes array is NULL-terminated
 */
static void	sort_and_print_env(char **env_array)
{
	int	i;

	i = 0;
	while (env_array[i])
	{
		printf("%s\n", env_array[i]);
		i++;
	}
}

/*
 * Prints the environment variables in sorted export format.
 *   - Converts list to array of formatted strings
 *   - Sorts the array
 *   - Prints each entry
 *   - Frees allocated memory
 */
void	print_env(t_env *env)
{
	int		count;
	char	**env_array;

	count = env_size(env);
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return ;
	if (!fill_env_array(env_array, env))
	{
		free(env_array);
		return ;
	}
	insertion_sort(env_array, count);
	sort_and_print_env(env_array);
	free_env_array(env_array, count);
}