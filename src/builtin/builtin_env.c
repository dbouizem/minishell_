#include "../includes/minishell.h"

void	print_env(t_shell *shell)
{
	int	i;

	if (!shell || !shell->env)
		return ;
	i = 0;
	while (shell->env[i])
	{
		ft_putendl_fd(shell->env[i], STDOUT_FILENO);
		i++;
	}
}

int	builtin_env(char **args, t_shell *shell)
{
	if (args[1])
	{
		ft_putstr_fd("minishell: env: ", STDERR_FILENO);
		ft_putstr_fd("does not take arguments\n", STDERR_FILENO);
		return (1);
	}
	if (!shell || !shell->env)
		return (0);
	print_env(shell);
	return (0);
}
