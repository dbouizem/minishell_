/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:44:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/21 04:33:19 by dbouizem         ###   ########.fr       */
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

static void	print_exit_prompt(t_shell *shell)
{
	if (shell && shell->interactive
		&& isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		write(STDERR_FILENO, "exit\n", 5);
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

int	builtin_exit(char **args, t_shell *shell)
{
	long long	exit_code;
	int			overflow;
	int			status;

	print_exit_prompt(shell);
	if (!args[1])
	{
		if (shell)
			status = shell->exit_status;
		else
			status = 0;
		return (set_exit_status(shell, status, 1));
	}
	if (!is_numeric_arg(args[1]))
		return (handle_numeric_error(args[1], shell));
	if (args[2])
	{
		print_exit_error(NULL, "too_many");
		return (1);
	}
	exit_code = ft_atoll(args[1], &overflow);
	if (overflow)
		return (handle_numeric_error(args[1], shell));
	status = (unsigned char)(exit_code % 256);
	return (set_exit_status(shell, status, 1));
}
