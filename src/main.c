#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void	print_startup(void)
{
	display_welcome();
	printf("%s=== Minishell Started ===%s\n", GREEN, RESET);
	printf("%sType 'exit' to quit%s\n", CYAN, RESET);
}

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
	if (!input)
	{
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
	print_startup();
	while (shell_cycle(&shell))
		;
	cleanup_shell(&shell);
	printf("%sGoodbye!%s\n", RED, RESET);
	return (shell.exit_status);
}
