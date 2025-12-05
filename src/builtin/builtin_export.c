#include "../includes/minishell.h"

static void	print_var(t_shell *shell)
{
	int		i;
	char	*new;

	i = 0;
	while (shell->env[i])
	{
		new = ft_strchr(shell->env[i], '=');
		if (new)
		{
			write(1, shell->env[i], new - shell->env[i]);
			printf("=\"%s\"\n", new + 1);
		}
		else
			printf("%s\n", shell->env[i]);
		i++;
	}
}

static int	is_valid_name(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] && ft_isdigit(arg[0]))
		return (1);
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '_')
		{
			if (!arg[i + 1] || arg[i + 1] == '=')
				break ;
			i++;
		}
		if (!ft_isalnum(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	export_val(char *arg, t_shell *shell)
{
	char	*egal;
	char	*var;
	char	*value;
	int		status;

	egal = ft_strchr(arg, '=');
	if (is_valid_name(arg))
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd("not an identifier: ", 2);
		ft_putendl_fd(arg, 2);
		return (1);
	}
	if (egal)
	{
		var = ft_substr(arg, 0, egal - arg);
		value = egal + 1;
		if (!var)
			return (1);
		status = set_env_value(var, value, shell);
		free(var);
		return (!status);
	}
	else
		status = set_env_value(arg, "", shell);
	return (0);
}

int	builtin_export(char **args, t_shell *shell)
{
	int	exit_status;
	int	i;

	exit_status = 0;
	//sans argument
	if (!args[1])
	{
		print_var(shell);
		return (0);
	}
	//avec 1 ou plusieurs arguments
	i = 1;
	while (args[i])
	{
		if (export_val(args[i], shell))
			exit_status = 1;
		i++;
	}
	return (exit_status);
}
