/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01exp_squot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 21:17:59 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/25 19:03:25 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

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
	while (str_quote[i])
	{
		if (str_quote[i] != quote)
			res[j++] = str_quote[i];
		i++;
	}
	res[j] = '\0';
	free(str_quote);
	return (res);
}

void	ft_is_squoted(t_command *cmds, char quote)
{
	int		i;

	while (cmds)
	{
		i = 0;
		while (cmds->argv && cmds->argv[i])
		{
			if (ft_strchr(cmds->argv[i], quote))
				cmds->argv[i] = ft_remove_quotes(cmds->argv[i], quote);
			i++;
		}
		if (cmds->redir_in)
			if (ft_strchr(cmds->redir_in, quote))
				cmds->redir_in = ft_remove_quotes(cmds->redir_in, quote);
		if (cmds->redir_out)
			if (ft_strchr(cmds->redir_out, quote))
				cmds->redir_out = ft_remove_quotes(cmds->redir_out, quote);
		cmds = cmds->next;
	}
}
