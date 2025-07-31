/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:49:27 by jucoelho          #+#    #+#             */
/*   Updated: 2025/07/30 21:42:58 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

int ft_handle_expander(char *input, int i, t_shell *shell, t_token **tokens)
{
	char	*temp;
	char	*var;
	int		j;

	j = 0;
	//printf("entrou handle_expander\n\n\n\n");
	if (input[i++] == '?')
		return(shell->status);
	else
	{
		//printf("entrou else, i= %d, j = %d, input = %s\n", i, j, input);
		while (input[i] && input[i] != ' ' && input[i] != '"' && input[i] != '\'' && input[i] != '>' && input[i] != '<' && input[i] != '|') 
		{
			j++;
			i++;
		//	printf("while, i= %d, j = %d, input = %s\n", i, j, input);
		}
		//printf("saiu do while, i= %d, j = %d, input = %s\n", i, j, input);
		temp = (char *)malloc ((sizeof(char)) * j + 1);
		i = i - j;
		temp = ft_substr(input, i, j);
		if (!temp)
			return (0);
		var = env_var(shell->envp, temp);
		free(temp);
		if(!var)
			return(0);
		temp = ft_strdup(var);
		ft_handle_word(temp, 0, tokens);
		free(temp);
	}
	return(i + j);
}