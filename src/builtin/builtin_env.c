#include "../includes/minishell.h"

void	print_env(t_shell *shell)
{
	int	i;

	if (!shell || !shell->env)
		return ;
	i = 0;
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
}

int	builtin_env(t_shell *shell)
{
	if (!shell || !shell->env)
		return (125);
	print_env(shell);
	return (0);
}
