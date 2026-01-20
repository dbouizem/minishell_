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

static char	*get_input(t_shell *shell)
{
	if (shell->interactive)
		return (read_input());
	return (read_input_non_interactive());
}

static int	handle_sigint(t_shell *shell, char *input)
{
	shell->exit_status = 130;
	free(input);
	shell->current_input = NULL;
	g_signal = 0;
	return (1);
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
	input = get_input(shell);
	shell->current_input = input;
	if (g_signal == SIGINT)
		return (handle_sigint(shell, input));
	return (finish_cycle(shell, input));
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	setup_signals();
	while (shell_cycle(&shell))
		;
	cleanup_shell(&shell);
	return (shell.exit_status);
}
