#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*input;
	int		should_exit;

	(void)argc;
	(void)argv;
	display_welcome();
	init_shell(&shell, envp);
	printf("%s=== Minishell Started ===%s\n", GREEN, RESET);
	printf("%sType 'exit' to quit or Ctrl+D%s\n", CYAN, RESET);
	while (1)
	{
		if (shell.interactive)
			input = read_input();
		else
			input = read_input_non_interactive();
		if (!input)
			break ;
		should_exit = process_input(input, &shell);
		free(input);
		if (should_exit)
			break ;
	}
	cleanup_shell(&shell);
	printf("%sGoodbye!%s\n", RED, RESET);
	return (shell.exit_status);
}
