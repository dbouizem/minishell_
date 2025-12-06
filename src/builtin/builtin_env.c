#include "../includes/minishell.h"

void	print_env(t_shell *shell)
{
<<<<<<< HEAD
	int i;
=======
	int	i;
>>>>>>> origin/5-exec

	if (!shell || !shell->env)
		return ;
	i = 0;
	while (shell->env[i])
	{
<<<<<<< HEAD
		printf("%s\n", shell->env[i]);
=======
		ft_putendl_fd(shell->env[i], STDOUT_FILENO);
>>>>>>> origin/5-exec
		i++;
	}
}

<<<<<<< HEAD
int		builtin_env(t_shell *shell)
{
	if (!shell || !shell->env)
		return (125);
=======
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
>>>>>>> origin/5-exec
	print_env(shell);
	return (0);
}
