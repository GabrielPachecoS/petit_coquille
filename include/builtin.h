/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:54:54 by gapachec          #+#    #+#             */
/*   Updated: 2025/06/30 19:57:03 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

void	exec_builtin(char **args, t_shell *shell);
int	is_builtin(char *cmd);

int	builtin_cd(char **args, t_shell *shell);
int	builtin_echo(char **args);
int	builtin_env(t_env *env);
int	builtin_exit(char **args, t_shell *shell);
int	builtin_export(char **argv, t_env **env, t_shell *shell);
int	builtin_pwd(void);
int	builtin_unset(char **args, t_env **env);




#endif
