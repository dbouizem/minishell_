#include "../../includes/minishell.h"

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

	if (shell && shell->interactive
		&& isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		write(STDERR_FILENO, "exit\n", 5);
	if (!args[1])
		exit(shell->exit_status);
	if (!is_numeric_arg(args[1]))
	{
		print_exit_error(args[1], "numeric");
		exit(2);
	}
	if (args[2])
	{
		print_exit_error(NULL, "too_many");
		return (1);
	}
	exit_code = ft_atoll(args[1], &overflow);
	if (overflow)
	{
		print_exit_error(args[1], "numeric");
		exit(2);
	}
	exit((unsigned char)(exit_code % 256));
}
