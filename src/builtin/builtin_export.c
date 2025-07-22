/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <gapachec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:58:27 by gapachec          #+#    #+#             */
/*   Updated: 2025/07/16 19:37:44 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

/*
 * Checks if a string is a valid environment variable identifier.
 *   - Must start with a letter or underscore
 *   - Followed by alphanumeric characters or underscores
 *   - Stops checking at the '=' character, if present
 */
static int	is_valid_identifier(const char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/*
 * Splits a 'key=value' argument into key and value.
 *   - Sets `has_value` to 1 if '=' is found
 *   - If '=' is missing, value is set to NULL
 */
static void	extract_key_value(char *arg, char **key,
	char **value, int *has_value)
{
	char	*equal;

	equal = ft_strchr(arg, '=');
	*has_value = 0;
	if (equal)
	{
		*has_value = 1;
		*key = ft_substr(arg, 0, equal - arg);
		*value = ft_strdup(equal + 1);
	}
	else
	{
		*key = ft_strdup(arg);
		*value = NULL;
	}
}

/*
 * Processes a single export argument.
 *   - Validates the identifier format
 *   - Extracts key and value
 *   - Updates or adds the variable to the environment
 *   - On error, prints a message and sets exit status to 1
 */
static int	handle_export_argument(char *arg, t_env **env, t_shell *shell)
{
	char	*key;
	char	*value;
	int		has_value;
	int		result;

	if (!is_valid_identifier(arg))
	{
		write(2, " not a valid identifier\n", 24);
		shell->last_exit_status = 1;
		return (1);
	}
	extract_key_value(arg, &key, &value, &has_value);
	result = update_or_add_env(env, key, value, has_value);
	return (result);
}

/*
 * Implements the 'export' builtin.
 *   - If no arguments, prints the environment
 *   - Otherwise, processes each argument as a key or key=value pair
 *   - Returns 1 if any invalid identifiers were found
 */
int	builtin_export(char **argv, t_env **env, t_shell *shell)
{
	int	i;
	int	any_errors;

	if (!argv[1])
	{
		print_env(*env);
		return (0);
	}
	i = 1;
	any_errors = 0;
	while (argv[i])
	{
		if (handle_export_argument(argv[i], env, shell))
			any_errors = 1;
		i++;
	}
	return (any_errors);
}
