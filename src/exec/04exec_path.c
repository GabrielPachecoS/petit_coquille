/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04exec_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:01:30 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/19 18:49:39 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_report_cmd_not_found(char *cmd)
{
	printf("%s: command not found\n", cmd);
	exit(127);
}

static char	*ft_build_fullpath(char *path, char *cmd)
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

static char	*ft_get_path_variable(t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 5) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static char	*ft_search_cmd_in_paths(char **paths, char *cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = ft_build_fullpath(paths[i], cmd);
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
	return (ft_report_cmd_not_found(cmd));
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
			return (ft_report_cmd_not_found(cmd));
	}
	path_value = ft_get_path_variable(env);
	if (!path_value)
		return (ft_report_cmd_not_found(cmd));
	paths = ft_split(path_value, ':');
	if (!paths)
		return (ft_report_cmd_not_found(cmd));
	return (ft_search_cmd_in_paths(paths, cmd));
}
