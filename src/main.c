/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:31:15 by gapachec          #+#    #+#             */
/*   Updated: 2025/08/19 00:40:20 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

int	var_global = 0;

static void print_fds(const char *when)
{
    DIR *dir = opendir("/proc/self/fd");
    struct dirent *entry;

    if (!dir)
        return;

    printf("\n[FDs abertos %s]:\n", when);
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] != '.')
            printf("  FD: %s\n", entry->d_name);
    }
    closedir(dir);
}

int	main(int argc, char **argv, char **envp)
{
	print_fds("ANTES\n");
	t_shell	shell;
	(void)argc;
	(void)argv;
	ft_init_struct(&shell, envp);
	ft_handle_signals();
	ft_start_minishell(&shell);
	print_fds("DEPOIS\n");
	return (0);
}
