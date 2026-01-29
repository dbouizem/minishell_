/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:54:23 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/29 18:54:21 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int is_valid_identifier(char c)
{
	return (c == '_' || c == '+' || c == '=' || c == '-');
}

static int	is_invalid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (1);
	if (!ft_isalnum(str[0]) && !is_valid_identifier(str[0]))
		return (1);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i + 1] == '-')
			return (1);
		i++;
	}
	return (0);
}

int	builtin_unset(char **args, t_shell *shell)
{
	int	i;
	int	has_error;

	if (!args[1])
		return (0);
	has_error = 0;
	i = 1;
	while (args[i])
	{
		if (is_invalid_identifier(args[i]))
		{
			print_unset_error(args[i]);
			has_error = 1;
		}
		else
			unset_env_value(args[i], shell);
		i++;
	}
	return (has_error);
}
