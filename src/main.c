#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

static char	*get_input(t_shell *shell)
{
	if (shell->interactive)
		return (read_input());
	return (read_input_non_interactive());
}

static int	shell_cycle(t_shell *shell)
{
	char	*input;

	g_signal = 0;
	input = get_input(shell);
	if (g_signal == SIGINT)
	{
		shell->exit_status = 130;
		free(input);
		g_signal = 0;
		return (1);
	}
	if (!input)
	{
		if (shell->interactive)
			printf("exit\n");
		return (0);
	}
	process_input(input, shell);
	free(input);
	g_signal = 0;
	return (1);
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
