#include "../includes/minishell.h"

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
