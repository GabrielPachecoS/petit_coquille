/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00expander.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:49:27 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/17 19:28:03 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

static int	ft_skip_quote(char c, int *state)
{
	if (c == '\'' && *state == 0)
		return (*state = 1, 1);
	if (c == '\'' && *state == 1)
		return (*state = 0, 1);
	if (c == '"' && *state == 0)
		return (*state = 2, 1);
	if (c == '"' && *state == 2)
		return (*state = 0, 1);
	return (0);
}

char	*ft_remove_quotes_by_context(char *str)
{
	char	*res;
	int		i;
	int		j;
	int		state;

	state = 0;
	i = 0;
	j = 0;
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (!ft_skip_quote(str[i], &state))
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	free(str);
	return (res);
}


static int	ft_must_expand(char *str)
{
	int	i;
	int	state;

	state = 0; // 0 = NORMAL, 1 = SQUOTE, 2 = DQUOTE
	i = 0;
	while (str[i])
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

t_command	*ft_remove_quotes_all(t_command *cmds)
{
	t_command	*head;
	int			i;

	head = cmds;
	while (cmds)
	{
		i = 0;
		while (cmds->argv && cmds->argv[i])
		{
			cmds->argv[i] = ft_remove_quotes_by_context(cmds->argv[i]);
			i++;
		}
		if (cmds->redir_in)
			cmds->redir_in = ft_remove_quotes_by_context(cmds->redir_in);
		if (cmds->redir_out)
			cmds->redir_out = ft_remove_quotes_by_context(cmds->redir_out);
		cmds = cmds->next;
	}
	return (head);
}

int	ft_needs_expansion(t_command *cmds)
{
	int	i;

	while (cmds)
	{
		i = 0;
		while (cmds->argv[i])
		{
			if (ft_strchr(cmds->argv[i], '$') && (ft_must_expand(cmds->argv[i]) == 1))
				return(1);
			i++;
		}
		if(cmds->redir_in)
		{
			if (ft_strchr(cmds->redir_in, '$') && (ft_must_expand(cmds->redir_in) == 1))
				return(1);
		}
		if(cmds->redir_out)
		{
			if (ft_strchr(cmds->redir_out, '$') && (ft_must_expand(cmds->redir_out) == 1))
				return(1);
		}
		cmds = cmds->next;
	}
	return(0);
}


t_command	*ft_expander(t_shell *shell, t_command *cmds)
{
	t_command *head;
	int	i;

	head = cmds;
	ft_is_squoted(cmds, '\'');
	cmds = head;
	ft_is_dquoted(cmds, shell, '"');
	cmds = head;
	while (cmds)
	{
		i = 0;
		while(cmds->argv[i])
		{
			cmds->argv[i] = ft_handle_expander(cmds->argv[i], shell);
			i++;
		}
		if (cmds->redir_in)
			cmds->redir_in = ft_handle_expander(cmds->redir_in, shell);
		if (cmds->redir_out)
			cmds->redir_out = ft_handle_expander(cmds->redir_out, shell);
		cmds = cmds->next;
	}
	return(head);
}
