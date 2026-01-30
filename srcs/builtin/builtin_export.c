/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:54:18 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/30 12:38:05 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_invalid_identifier(char *str, char stop_char)
{
	int	i;

	if (!str)
		return (2);
	if (!*str)
		return (1);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	i = 1;
	while (str[i] && str[i] != stop_char)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

static int	export_without_equal(char *arg, t_shell *shell)
{
	int	invalid;

	invalid = is_invalid_identifier(arg, '\0');
	if (invalid == 2)
	{
		print_exported_vars(shell);
		return (0);
	}
	if (invalid == 1)
	{
		print_export_error(arg);
		return (1);
	}
	return (0);
}

static int	export_with_append(char *arg, t_shell *shell)
{
	char	*plus_pos;
	char	*name;
	char	*old_value;
	char	*new_value;
	int		ret;

	plus_pos = ft_strchr(arg, '+');
	if (is_invalid_identifier(arg, '+'))
		return (print_export_error(arg), 1);
	name = ft_substr(arg, 0, plus_pos - arg);
	if (!name)
		return (1);
	old_value = get_env_value(name, shell);
	if (old_value)
		new_value = ft_strjoin(old_value, plus_pos + 2);
	else
		new_value = ft_strdup(plus_pos + 2);
	if (!new_value)
		return (free(name), 1);
	ret = set_env_value(name, new_value, shell);
	free(name);
	free(new_value);
	if (ret == 1)
		return (0);
	return (1);
}

static int	export_with_equal(char *arg, t_shell *shell)
{
	char	*equal_pos;
	char	*name;
	int		ret;

	if (ft_strstr(arg, "+="))
		return (export_with_append(arg, shell));
	equal_pos = ft_strchr(arg, '=');
	if (is_invalid_identifier(arg, '='))
	{
		print_export_error(arg);
		return (1);
	}
	name = ft_substr(arg, 0, equal_pos - arg);
	if (!name)
		return (1);
	ret = set_env_value(name, equal_pos + 1, shell);
	free(name);
	if (ret == 1)
		return (0);
	return (1);
}

int	builtin_export(char **args, t_shell *shell)
{
	int	exit_status;
	int	i;
	int	func_result;

	exit_status = 0;
	if (!args[1])
	{
		print_exported_vars(shell);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
			func_result = export_with_equal(args[i], shell);
		else
			func_result = export_without_equal(args[i], shell);
		if (func_result == 1)
			exit_status = 1;
		i++;
	}
	return (exit_status);
}
