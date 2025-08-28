/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:37:19 by gapachec          #+#    #+#             */
/*   Updated: 2025/08/28 15:42:22 by jucoelho         ###   ########.fr       */
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
}				t_env;

//00env_init.c
t_env	*env_init(char **envp);
t_env	*env_pair_create(char *key, char *value);
void	env_list_append(t_env **env, t_env *new_node);

//01env_to_array.c
int		env_size(t_env *env);
void	free_env_array(char **array, int size);
char	**env_to_array(t_env *env);

//02env_set_unset.c
int		set_env_value(t_env **env, const char *key, const char *value);
int		unset_env_key(t_env **env, const char *key);

//03env_print.c
void	print_env(t_env *env);

//04env_utils.c
char	*env_var(t_env *env, const char *key);
int		update_or_add_env(t_env **env, char *key, char *value, int has_value);
t_env	*env_lookup(t_env *env, const char *key);

//05env_free.c
void	env_node_destroy(t_env *env);
void	env_destroy(t_env *env);

#endif