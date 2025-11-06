#include "../includes/minishell.h"

static char	**copy_env(char **envp)
{
	char	**new_env;
	int		count;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}

void	init_shell(t_shell *shell, char **envp)
{
	shell->exit_status = 0;
	shell->env = copy_env(envp);
	if (!shell->env)
	{
		printf("Error: Failed to initialize environment\n");
		exit(1);
	}
	printf("%s=== Minishell Started ===%s\n", GREEN, RESET);
	printf("%sType 'exit' to quit or Ctrl+D%s\n", CYAN, RESET);
}

void	cleanup_shell(t_shell *shell)
{
	int	i;

	if (shell->env)
	{
		i = 0;
		while (shell->env[i])
		{
			free(shell->env[i]);
			i++;
		}
		free(shell->env);
		shell->env = NULL;
	}
	rl_clear_history();
	printf("%sGoodbye!%s\n", RED, RESET);
}
