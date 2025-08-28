/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03exp_quot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 21:33:48 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/28 16:22:23 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_skip_quote(char c, int *state)
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

char	*ft_remove_quotes(char *str_quote, char quote)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = malloc(ft_strlen(str_quote) - 1);
	if (!res)
		return (NULL);
	while (str_quote && str_quote[i])
	{
		if (str_quote[i] != quote)
			res[j++] = str_quote[i];
		i++;
	}
	res[j] = '\0';
	free(str_quote);
	return (res);
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
	while (str && str[i])
	{
		if (!ft_skip_quote(str[i], &state))
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	free(str);
	return (res);
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
