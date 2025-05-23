/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:35:26 by gapachec          #+#    #+#             */
/*   Updated: 2025/05/23 17:09:20 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_start_minishell(t_shell *shell)
{
	char	*input;
	t_token	*tokens;
	t_command *cmds; 

	(void)shell;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (*input)
			add_history(input);

		tokens = ft_lexer(input);
		ft_print_tokens(tokens);
		cmds = ft_parser(tokens);
		ft_print_commands(cmds);
		ft_exec_cmds(shell, cmds);
		ft_free_commands(cmds);
		ft_free_tokens(tokens);
		ft_cleanup(input);
	}
}
