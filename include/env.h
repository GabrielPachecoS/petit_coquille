/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:37:19 by gapachec          #+#    #+#             */
/*   Updated: 2025/07/01 14:46:27 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

t_env	*env_init(char **envp);

void	env_destroy(t_env *env);

char	*env_lookup(t_env *env, const char *key);

char	**env_to_array(t_env *env);

int		set_env_value(t_env **env, const char *key, const char *value);
int		unset_env_key(t_env **env, const char *key);

#endif
