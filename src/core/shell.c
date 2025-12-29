#include "../../includes/minishell.h"

void	init_shell(t_shell *shell, char **envp)
{
	ft_memset(shell, 0, sizeof(t_shell));
	shell->exit_status = 0;
	shell->env = NULL;
	shell->env_list = NULL;
	shell->interactive = isatty(STDIN_FILENO)
		&& isatty(STDOUT_FILENO);
	if (shell->interactive)
	{
		rl_catch_signals = 0;
		rl_catch_sigwinch = 0;
		if (tcgetattr(STDIN_FILENO, &shell->original_term) == -1)
			shell_error("tcgetattr", 1);
	}
	shell->env_list = env_array_to_list(envp);
	if (!shell->env_list && envp && *envp)
		shell_error("Failed to initialize environment list", 1);
	env_list_to_array(shell);
}

void	cleanup_shell(t_shell *shell)
{
	int	i;

	if (shell->interactive
		&& tcsetattr(STDIN_FILENO, TCSANOW, &shell->original_term) == -1)
		perror("minishell: tcsetattr");
	if (shell->env)
	{
		i = 0;
		while (shell->env[i])
			free(shell->env[i++]);
		free(shell->env);
		shell->env = NULL;
	}
	if (shell->env_list)
	{
		free_env_list(shell->env_list);
		shell->env_list = NULL;
	}
	rl_clear_history();
}
