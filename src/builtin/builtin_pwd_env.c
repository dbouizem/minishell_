#include "../includes/minishell.h"

int	builtin_env(t_shell *shell)
{
	if (!shell || !shell->env)
		return (1);
	print_env(shell);
	return (0);
}

int	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("minishell: pwd");
		return (1);
	}
}
