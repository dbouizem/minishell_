#include "minishell.h"
#include "colors.h"

void	init_shell(t_shell *shell, char **envp)
{
	shell->exit_status = 0;
	(void)envp;
	printf("%s=== Minishell Started ===%s\n", GREEN, RESET);
	printf("%sType 'exit' to quit or Ctrl+D%s\n", CYAN, RESET);
}

void	cleanup_shell(t_shell *shell)
{
	(void)shell;
	rl_clear_history();
	printf("%sGoodbye!%s\n", RED, RESET);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*input;

	(void)argc;
	(void)argv;

	init_shell(&shell, envp);
	while (1)
	{
		display_prompt();
		input = read_input();
		if (!input)
			break ;
		printf("%sYou typed%s %s\n", BLUE, RESET, input);
		free(input);
	}
	cleanup_shell(&shell);
	return (0);
}

