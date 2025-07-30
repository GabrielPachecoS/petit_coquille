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

int	ft_is_builtin(t_command *cmds);
void	ft_exec_simplebuiltin(t_shell *shell, char **args);
int	is_numeric(const char *str);

int	ft_builtin_cd(char **args, t_shell *shell);
int	ft_builtin_echo(char **args);
int	ft_builtin_env(t_env *env);
int	ft_builtin_exit(char **args, t_shell *shell);
int	ft_builtin_export(char **args, t_env **env, t_shell *shell);
int	ft_builtin_pwd(void);
int	ft_builtin_unset(char **args, t_env **env);

#endif
