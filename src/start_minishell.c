/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:35:26 by gapachec          #+#    #+#             */
/*   Updated: 2025/08/11 21:02:36 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "frescurinha.h"

void	ft_init_struct(t_shell *shell, char **envp)
{
	shell->envp = env_init(envp);
	shell->last_exit_status = 0;
	shell->status = 0;
	shell->should_exit = -1;
	shell->exit_code = -1;
	shell->fd[0] = -1;
	shell->fd[1] = -1;
	shell->prev_fd = -1;
	shell->append = -1;
	shell->heredoc = NULL;
	shell->infile = NULL;
	shell->outfile = NULL;
}

void	ft_free_shell(t_shell *shell)
{
	shell->last_exit_status = 0;
	shell->exit_code = -1;
	shell->fd[0] = -1;
	shell->fd[1] = -1;
	shell->prev_fd = -1;
	shell->append = -1;
	if (shell->heredoc)
		free(shell->heredoc);
	if (shell->infile)
		free(shell->infile);
	if (shell->outfile)
		free(shell->outfile);
	shell->heredoc = NULL;
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
		tokens = NULL;
		cmds = NULL;
		input = readline(FRESCURINHA);
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (*input)
			add_history(input);
		tokens = ft_lexer(input, shell);
		//ft_print_tokens(tokens);
		if(tokens)
			cmds = ft_parser(tokens, shell);
		//ft_print_commands(shell, cmds);
		if(cmds)
			ft_exec(shell, cmds);
		if (cmds)
			ft_free_commands(cmds);
		if (tokens)
			ft_free_tokens(tokens);
		ft_free_shell(shell);
		if (shell->should_exit == 1)
		 	exit(shell->status);
	}
	ft_cleanup(shell, input);
}
