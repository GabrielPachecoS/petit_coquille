/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:58:17 by gapachec          #+#    #+#             */
/*   Updated: 2025/07/01 19:01:21 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

int	builtin_cd(char **args, t_env **env)
{
	char	*path;
	char	*oldpwd;

	if (!args[1])
		return (0);
	oldpwd = getcwd(NULL, 0);
	if (chdir(args[1]) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	set_env_value(env, "OLDPWD", oldpwd);
	free(oldpwd);
	path = getcwd(NULL, 0);
	set_env_value(env, "PWD", path);
	free(path);
	return (0);
}
