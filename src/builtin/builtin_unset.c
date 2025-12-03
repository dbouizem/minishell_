#include "../includes/minishell.h"

static int	is_valid_name(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] && ft_isdigit(arg[0]))
		return (1);
	while (arg[i])
	{
		if (arg[i] == '_')
		{
			if (!arg[i + 1])
				break ;
			i++;
		}
		if (!ft_isalnum(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

int	builtin_unset(char **args, t_shell *shell)
{
	int i;

	i = 1;
	if (!args || !*args)
		return (1);
	while (args[i])
	{
		//Invalid NAME param
		if (is_valid_name(args[i]))
		{
			ft_putstr_fd("minishell: export: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd(": invalid parameter name", 2);
			return (1);
		}
		//Enlever la variable si elle existe
		else
			unset_env_value(args[i], shell);
		i++;
	}
	return (0);
}
