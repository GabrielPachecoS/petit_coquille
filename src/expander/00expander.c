/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00expander.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:49:27 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/28 16:22:11 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_must_expand(char *str)
{
	int	i;
	int	state;

	state = 0;
	i = 0;
	if (!str || !ft_strchr(str, '$'))
		return (0);
	while (str && str[i])
	{
		if (str[i] == '\'' && state == 0)
			state = 1;
		else if (str[i] == '\'' && state == 1)
			state = 0;
		else if (str[i] == '"' && state == 0)
			state = 2;
		else if (str[i] == '"' && state == 2)
			state = 0;
		else if (str[i] == '$' && state != 1)
			return (1);
		i++;
	}
	return (0);
}

int	ft_needs_expansion(t_command *cmds)
{
	int	i;

	while (cmds)
	{
		i = 0;
		while (cmds->argv && cmds->argv[i])
		{
			if (ft_must_expand(cmds->argv[i]) == 1)
				return (1);
			i++;
		}
		if (cmds->redir_in)
		{
			if (ft_must_expand(cmds->redir_in) == 1)
				return (1);
		}
		if (cmds->redir_out)
		{
			if (ft_must_expand(cmds->redir_out) == 1)
				return (1);
		}
		cmds = cmds->next;
	}
	return (0);
}

void	ft_expand_swap(char **p, t_shell *sh)
{
	char	*old;
	char	*new;

	old = *p;
	new = ft_handle_expander(old, sh);
	if (!new)
		new = ft_strdup("");
	free(old);
	*p = new;
}

t_command	*ft_expander(t_shell *shell, t_command *cmds)
{
	t_command	*head;
	int			i;

	head = cmds;
	ft_is_squoted(cmds, '\'');
	cmds = head;
	ft_is_dquoted(cmds, shell, '"');
	cmds = head;
	while (cmds)
	{
		i = 0;
		while (cmds->argv[i])
			ft_expand_swap(&cmds->argv[i++], shell);
		if (cmds->redir_in)
			ft_expand_swap(&cmds->redir_in, shell);
		if (cmds->redir_out)
			ft_expand_swap(&cmds->redir_out, shell);
		cmds = cmds->next;
	}
	return (head);
}
