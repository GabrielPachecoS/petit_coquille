/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03exp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 21:33:48 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/16 23:48:08 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

/*static char	*ft_expquoted_continue(char *input, t_shell *shell)
{
	int	z;

	z = shell->len;
	if (ft_isalpha(input[z]) || input[z] == '_')
	{
		z++;
		while (ft_isalnum(input[z]))
			z++;
	}
	if (input[z] != '"')
		return (input);
	if (input[shell->len] == '{')
	{
		++shell->len;
		return (ft_handle_braces(input, shell));
	}
	input = ft_handle_expalnum(input, shell);
	return (input);
}*/

/*static char	*ft_expquoted(char *input, t_shell *shell)
{
	char	*var;

	if (input[shell->len] == '{')
		return (ft_handle_braces(input, shell));
	if (input[shell->len] == '?')
	{
		if (input[shell->len + 1] == '"')
		{
			var = ft_itoa(shell->status);
			if (!var)
				return (0);
			//shell->start = ft_handle_word(var, 0);
			free(var);
			return (input);
		}
		return (input);
	}
	return (ft_expquoted_continue(input, shell));
}

static char	*ft_handle_special_cases(char *str_quoted, t_shell *shell)
{
	char	*var;
	int		i;

	i = 1;
	if (str_quoted[i] == '$')
	{
		var = ft_itoa(shell->status);
		if (!var)
			return (0);
		str_quoted = var;
		free(var);
		return t_shel (str_quoted);
	}
	if (str_quoted[i] == '{')
	{
		++shell->start;
		str_quoted = ft_handle_braces(str_quoted, shell);
	}
	else
	{
		str_quoted = ft_handle_expalnum(str_quoted, shell);
	}
	return (str_quoted);
}*/

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
		return (expanded ? ft_strdup(expanded) : ft_strdup(""));
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
		return (ft_expand_str(var, shell));;
	}
	else if (str_quoted[0] == '"')
	{
		if (str_quoted[1] == '?' && str_quoted[2] == '"')
		{
			shell->status = 0;
			return (ft_strdup("$"));
		}
		else if (str_quoted[1] == '$' && str_quoted[2] == '?' && str_quoted[4] == '\0')
			return (ft_itoa(shell->status));
	}
	return (ft_expand_str(str_quoted, shell));
}
