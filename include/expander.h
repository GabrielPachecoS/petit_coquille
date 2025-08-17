/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 21:37:24 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/17 15:20:16 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

//00 expander
t_command	*ft_expander(t_shell *shell, t_command *cmds);
t_command	*ft_remove_quotes_all(t_command *cmds);
int			ft_needs_expansion(t_command *cmds);
//01
char		*ft_remove_quotes(char *str_quote, char quote);
void		ft_is_squoted(t_command *cmds, char quote);
//02
void		ft_is_dquoted(t_command *cmds, t_shell *shell, char quote);
void		ft_is_redirquoted(t_command *cmds, t_shell *shell, char quote);
//03
char		*ft_handle_expander(char *input, t_shell *shell);
//04
char		*ft_expandvar(char *input, t_shell *shell);
char		*ft_handle_braces(char *input, t_shell *shell);
char		*ft_handle_expalnum(char *input, t_shell *shell);

#endif