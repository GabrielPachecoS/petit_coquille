/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 21:37:24 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/16 21:29:53 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

//00 expander
t_command	*ft_expander(t_shell *shell, t_command *cmds, t_token **tokens);
//01
char		*ft_remove_quotes(char *str_quote, char quote);
void		ft_is_squoted(t_command *cmds, char quote);
//02
void		ft_is_dquoted(t_command *cmds, t_shell *shell, t_token **tokens, char quote);
void		ft_is_redirquoted(t_command *cmds, t_shell *shell, t_token **tokens, char quote);
//03
char		*ft_handle_expander(char *input, int i, t_shell *shell, t_token **tokens);
//04
char		*ft_expandvar(char *input, t_shell *shell);
char		*ft_handle_braces(char *input, t_shell *shell, t_token **tokens);
char		*ft_handle_expalnum(char *input, t_shell *shell);

#endif