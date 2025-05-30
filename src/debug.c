#include "minishell.h"

void	ft_print_commands(t_command *cmd)
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
		if (cmd->redir_in)
			printf(" Redir entrada: %s\n", cmd->redir_in_file);
		if (cmd->redir_out)
			printf(" Redir saída: %s\n", cmd->redir_out_file);
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
