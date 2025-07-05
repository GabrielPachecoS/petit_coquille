/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:37:19 by gapachec          #+#    #+#             */
/*   Updated: 2025/07/04 18:46:58 by gapachec         ###   ########.fr       */
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
t_env	*env_pair_create(char *key, char *value);
void	env_list_append(t_env **env, t_env *new_node);

void	env_destroy(t_env *env);

char	*env_lookup(t_env *env, const char *key);

char	**env_to_array(t_env *env);

int		set_env_value(t_env **env, const char *key, const char *value);
int		unset_env_key(t_env **env, const char *key);

#endif
