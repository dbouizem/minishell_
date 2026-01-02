#include "../includes/minishell.h"

volatile sig_atomic_t g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*input;

	(void)argc;
	(void)argv;
	display_welcome();
	init_shell(&shell, envp);
	setup_signals();
	printf("%s=== Minishell Started ===%s\n", GREEN, RESET);
	printf("%sType 'exit' to quit%s\n", CYAN, RESET);
	while (1)
	{
		g_signal = 0;
		if (shell.interactive)
			input = read_input();
		else
			input = read_input_non_interactive();
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		process_input(input, &shell);
		free(input);
		g_signal = 0;
	}
	cleanup_shell(&shell);
	printf("%sGoodbye!%s\n", RED, RESET);
	return (shell.exit_status);
}
