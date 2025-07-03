/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:01:30 by jucoelho          #+#    #+#             */
/*   Updated: 2025/07/02 22:52:01 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_errorpath(char *cmd)
{
	printf("%s: command not found\n", cmd);
	return (NULL);
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

static char	*ft_find_cmdpath(t_env **env)
{
	int		i;

	i = 0;
	while ((env[i]))
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			return (env[i] + 5);
		}
		i++;
	}
	return (NULL);
}

static char	*ft_try_paths(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

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
	return (ft_errorpath(cmd));
}

char	*ft_get_cmdpath(char *cmd, t_env *env)
{
	char	*path_line;
	char	**paths;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
			return (ft_errorpath(cmd));
	}
	path_line = ft_find_cmdpath(env);
	if (!path_line)
		return (ft_errorpath(cmd));
	paths = ft_split(path_line, ':');
	if (!paths)
		return (ft_errorpath(cmd));
	return (ft_try_paths(paths, cmd));
}
