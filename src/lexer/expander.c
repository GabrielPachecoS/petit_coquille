/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:49:27 by jucoelho          #+#    #+#             */
/*   Updated: 2025/07/30 19:21:37 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_handle_expander(char *input, int i, t_shell *shell, t_token tokens)
{
	char	*temp;
	int		j;

	j = 0;
	if (input[i++] == '?')
		return(shell->status);
	else
	{
		while (input[i] && input[i] != ' ' && input[i] != '"' && input[i] != '\'' && input[i] != '>' && input[i] != '<' && input[i] != '|') 
			j++;
		temp = (char *)malloc ((sizeof(char)) * j + 1);
		i = i - j;
		temp = ft_substr(input, i, j);
		if (!getenv(temp))
		{
			free(temp);
			return(0);
		}
		else
		{
			ft_handle_word(temp, 0, &tokens);
			free(temp);
		}
	}
	return(i + j);
}