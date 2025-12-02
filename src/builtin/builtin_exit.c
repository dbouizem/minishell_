#include "../includes/minishell.h"

static int	is_number(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **args, t_shell *shell)
{
	int	exit_code;

	printf("exit\n");
	if (!args[1])
	{
		exit_code = shell->exit_status;
		cleanup_shell(shell);
		exit(exit_code);
	}
	if (!is_number(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		cleanup_shell(shell);
		exit(2);
	}
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	exit_code = ft_atoi(args[1]);
	cleanup_shell(shell);
	exit(exit_code & 255);
}