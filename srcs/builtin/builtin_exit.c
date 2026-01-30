/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:44:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/30 11:53:40 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_numeric_arg(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	set_exit_status(t_shell *shell, int status, int do_exit)
{
	if (shell)
	{
		shell->exit_status = status;
		if (do_exit)
			shell->should_exit = 1;
	}
	return (status);
}

static int	handle_numeric_error(char *arg, t_shell *shell)
{
	print_exit_error(arg, "numeric");
	return (set_exit_status(shell, 2, 1));
}

static int	exit_with_args(char **args, t_shell *shell)
{
	long long	exit_code;
	int			overflow;
	int			status;

	if (!is_numeric_arg(args[1]))
		return (handle_numeric_error(args[1], shell));
	if (args[2])
	{
		print_exit_error(NULL, "too_many");
		return (1);
	}
	exit_code = ft_atoll(args[1], &overflow);
	if (overflow && ft_strcmp(args[1], "-9223372036854775808") == 0)
	{
		overflow = 0;
		exit_code = LLONG_MIN;
	}
	if (overflow)
		return (handle_numeric_error(args[1], shell));
	status = (unsigned char)(exit_code % 256);
	return (set_exit_status(shell, status, 1));
}

int	builtin_exit(char **args, t_shell *shell)
{
	int	status;

	if (shell && shell->interactive
		&& isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		write(STDERR_FILENO, "exit\n", 5);
	if (!args[1])
	{
		status = 0;
		if (shell)
			status = shell->exit_status;
		return (set_exit_status(shell, status, 1));
	}
	return (exit_with_args(args, shell));
}
