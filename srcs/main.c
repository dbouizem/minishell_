/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:40:00 by dbouizem          #+#    #+#             */
/*   Updated: 2025/12/08 18:40:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

static int	handle_sigint(t_shell *shell, char *input)
{
	shell->exit_status = 130;
	free(input);
	shell->current_input = NULL;
	g_signal = 0;
	return (1);
}

static int	handle_sigquit(t_shell *shell, char *input)
{
	shell->exit_status = 131;
	shell->should_exit = 1;
	free(input);
	shell->current_input = NULL;
	g_signal = 0;
	return (0);
}

static int	finish_cycle(t_shell *shell, char *input)
{
	if (!input)
	{
		if (shell->interactive)
			ft_putendl_fd("exit", STDOUT_FILENO);
		return (0);
	}
	process_input(input, shell);
	free(input);
	shell->current_input = NULL;
	g_signal = 0;
	if (shell->should_exit)
		return (0);
	return (1);
}

static int	shell_cycle(t_shell *shell)
{
	char	*input;

	g_signal = 0;
	if (shell->interactive)
		input = read_input();
	else
		input = read_input_non_interactive();
	shell->current_input = input;
	if (g_signal == SIGINT)
		return (handle_sigint(shell, input));
	if (g_signal == SIGQUIT)
		return (handle_sigquit(shell, input));
	return (finish_cycle(shell, input));
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	init_shell(&shell, envp);
	if (!envp || !*envp)
		init_minimal_env(&shell, argv[0]);
	setup_signals();
	while (shell_cycle(&shell))
		;
	cleanup_shell(&shell);
	return (shell.exit_status);
}
