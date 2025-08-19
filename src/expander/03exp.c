/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03exp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 21:33:48 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/19 17:40:14 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

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

static char	*ft_expand_str(char *str_quoted, t_shell *shell)
{
	char	*temp;
	char	*chunk;
	int		i;

	i = 0;
	temp = ft_strdup("");
	while (str_quoted[i])
	{
		if (str_quoted[i] == '$' && str_quoted[i + 1])
			chunk = expand_dollar_block(str_quoted, &i, shell);
		else
			chunk = ft_substr(str_quoted, i++, 1);
		temp = ft_strjoin(temp, chunk);
	}
	return (temp);
}

char	*ft_handle_expander(char *str_quoted, t_shell *shell)
{
	char	*var;
	int		len;

	len = ft_strlen(str_quoted);
	if (str_quoted[0] == '"' && str_quoted[len - 1] == '"')
	{
		var = ft_strtrim(str_quoted, "\"");
		return (ft_expand_str(var, shell));
	}
	else if (str_quoted[0] == '"')
	{
		if (str_quoted[1] == '?' && str_quoted[2] == '"')
		{
			shell->status = 0;
			return (ft_strdup("$"));
		}
		else if (str_quoted[1] == '$' && str_quoted[2]
			== '?' && str_quoted[4] == '\0')
			return (ft_itoa(shell->status));
	}
	return (ft_expand_str(str_quoted, shell));
}
