#include "../includes/minishell.h"

static int	is_numeric_arg(char *str)
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
	long long	exit_code;
	int			overflow;

	write(STDERR_FILENO, "exit\n", 5);
	if (!args[1])
		exit(shell->exit_status);
	if (!is_numeric_arg(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		cleanup_shell(shell);
		exit(2);
	}
	if (args[2])
		return (ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO), 1);
	exit_code = ft_atoll(args[1], &overflow);
	if (overflow)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(2);
	}
	cleanup_shell(shell);
	exit((unsigned char)(exit_code % 256));
}
