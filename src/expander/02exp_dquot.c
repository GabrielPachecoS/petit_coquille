/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02exp_dquot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 21:24:12 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/28 16:22:19 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_double_quoted(char *str_quoted, t_shell *shell)
{
	char	*var;
	char	*tmp;
	int		len;

	len = ft_strlen(str_quoted);
	if (len >= 2 && str_quoted[0] == '"' && str_quoted[len - 1] == '"')
	{
		var = ft_strtrim(str_quoted, "\"");
		if (!var)
			return (ft_strdup(""));
		tmp = ft_expand_str(var, shell);
		free(var);
		if (tmp)
			return (tmp);
		return (ft_strdup(""));
	}
	if (str_quoted[0] == '"' && str_quoted[1] == '?' && str_quoted[2] == '"')
		return (ft_strdup("$"));
	if (str_quoted[0] == '"' && str_quoted[1] == '$'
		&& str_quoted[2] == '?' && str_quoted[4] == '\0')
		return (ft_itoa(shell->status));
	return (NULL);
}

void	ft_is_redirquoted(t_command *cmds, t_shell *shell, char quote)
{
	char	*old;

	if (cmds->redir_in && ft_strchr(cmds->redir_in, quote))
	{
		if (ft_strchr(cmds->redir_in, '$'))
			ft_expand_swap(&cmds->redir_in, shell);
		else
		{
			old = cmds->redir_in;
			cmds->redir_in = ft_remove_quotes(old, quote);
			free(old);
		}
	}
	if (cmds->redir_out && ft_strchr(cmds->redir_out, quote))
	{
		if (ft_strchr(cmds->redir_out, '$'))
			ft_expand_swap(&cmds->redir_out, shell);
		else
		{
			old = cmds->redir_out;
			cmds->redir_out = ft_remove_quotes(old, quote);
			free(old);
		}
	}
}

void	ft_is_dquoted(t_command *cmds, t_shell *shell, char quote)
{
	int		i;
	char	*old;

	while (cmds)
	{
		i = 0;
		while (cmds->argv && cmds->argv[i])
		{
			if (ft_strchr(cmds->argv[i], quote))
			{
				if (ft_strchr(cmds->argv[i], '$'))
					ft_expand_swap(&cmds->argv[i], shell);
				else
				{
					old = cmds->argv[i];
					cmds->argv[i] = ft_remove_quotes(old, quote);
					free(old);
				}
			}
			i++;
		}
		ft_is_redirquoted(cmds, shell, quote);
		cmds = cmds->next;
	}
}
