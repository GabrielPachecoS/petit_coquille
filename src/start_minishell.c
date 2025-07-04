/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:35:26 by gapachec          #+#    #+#             */
/*   Updated: 2025/07/04 01:14:03 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_struct(t_shell *shell, char **envp)
{
	shell->envp = env_init(envp);
	shell->last_exit_status = 0;
	shell->fd_in = -1;
	shell->fd_out = -1;
	shell->fd[0] = -1;
	shell->fd[1] = -1;
	shell->infile = NULL;
	shell->outfile = NULL;
}

void	ft_start_minishell(t_shell *shell)
{
	char		*input;
	t_token		*tokens;
	t_command	*cmds;

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
		cmds = ft_parser(tokens, *shell);
		ft_print_commands(shell, cmds);
		ft_exec_cmds(shell, cmds);
		ft_free_commands(cmds);
		ft_free_tokens(tokens);
		ft_cleanup(input);
	}
}
