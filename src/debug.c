#include "minishell.h"

void	ft_print_commands(t_shell *shell, t_command *cmd)
{
	int	i;

	while (cmd)
	{
		i = 0;
		printf("Comando:\n");
		if (cmd->argv)
		{
			while (cmd->argv[i])
			{
				printf(" argv[%d]: %s\n", i, cmd->argv[i]);
				i++;
			}
		}
		if (shell->infile)
			printf(" Redir entrada: %s\n", shell->infile);
		if (shell->outfile)
			printf(" Redir saída: %s\n", shell->outfile);
		cmd = cmd->next;
	}
}

void	ft_print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: [%d] \"%s\"\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
}
