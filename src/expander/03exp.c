/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03exp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 21:33:48 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/27 15:59:45 by jucoelho         ###   ########.fr       */
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
		{
			return (ft_strdup(""));
		}
	}
	(*i)++;
	return (ft_strdup("$"));
}

static char	*ft_expand_str(char *str_quoted, t_shell *shell)
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


static char	*expand_double_quoted(char *str_quoted, t_shell *shell)
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

char	*ft_handle_expander(char *str_quoted, t_shell *shell)
{
	char	*tmp;

	if (!str_quoted)
		return (ft_strdup(""));
	if (str_quoted[0] == '"')
	{
		tmp = expand_double_quoted(str_quoted, shell);
		if (tmp)
			return (tmp);
	}
	tmp = ft_expand_str(str_quoted, shell);
	if (tmp)
		return (tmp);
	return (ft_strdup(""));
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
