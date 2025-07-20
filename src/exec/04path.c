/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04path.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:01:30 by jucoelho          #+#    #+#             */
/*   Updated: 2025/07/16 18:37:25 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*report_cmd_not_found(char *cmd)
{
	printf("%s: command not found", cmd);
	return (NULL);
}

static char	*build_fullpath(char *path, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	return (full_path);
}

static char	*get_path_variable(t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 5) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static char	*search_cmd_in_paths(char **paths, char *cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = build_fullpath(paths[i], cmd);
		if (!full_path)
		{
			ft_free_split(paths);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			ft_free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(paths);
	return (report_cmd_not_found(cmd));
}

char	*ft_get_cmdpath(char *cmd, t_env *env)
{
	char	*path_value;
	char	**paths;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
			return (report_cmd_not_found(cmd));
	}
	path_value = get_path_variable(env);
	if (!path_value)
		return (report_cmd_not_found(cmd));
	paths = ft_split(path_value, ':');
	if (!paths)
		return (report_cmd_not_found(cmd));
	return (search_cmd_in_paths(paths, cmd));
}
