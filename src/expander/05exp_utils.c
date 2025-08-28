/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05exp_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:53:51 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/28 16:18:34 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_dollar_block(char *str, int *i, t_shell *shell)
{
	char	*chunk;
	char	*expanded;
	int		start;

	if (str[*i + 1] == '?')
	{
		*i += 2;
		return (ft_itoa(shell->status));
	}
	else if (ft_isalpha(str[*i + 1]) || str[*i + 1] == '_')
	{
		start = ++(*i);
		while (ft_isalnum(str[*i]) || str[*i] == '_')
			(*i)++;
		chunk = ft_substr(str, start, *i - start);
		expanded = env_var(shell->envp, chunk);
		free(chunk);
		if (expanded)
			return (ft_strdup(expanded));
		else
			return (ft_strdup(""));
	}
	(*i)++;
	return (ft_strdup("$"));
}

char	*ft_expand_str(char *str_quoted, t_shell *shell)
{
	char	*temp;
	char	*chunk;
	char	*joined;
	int		i;

	i = 0;
	temp = ft_strdup("");
	while (str_quoted && str_quoted[i])
	{
		if (str_quoted[i] == '$' && str_quoted[i + 1])
			chunk = expand_dollar_block(str_quoted, &i, shell);
		else
			chunk = ft_substr(str_quoted, i++, 1);
		if (!chunk)
		{
			free(temp);
			free(str_quoted);
			return (NULL);
		}
		joined = ft_strjoin(temp, chunk);
		free(temp);
		free(chunk);
		temp = joined;
	}
	return (temp);
}