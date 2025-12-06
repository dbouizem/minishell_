#include "../includes/minishell.h"

<<<<<<< HEAD
static void	print_var(t_shell *shell)
{
	int		i;
	char	*new;
=======
static void	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

static void	print_exported_vars(t_shell *shell)
{
	int		i;
	char	*equal_pos;
>>>>>>> origin/5-exec

	i = 0;
	while (shell->env[i])
	{
<<<<<<< HEAD
		new = ft_strchr(shell->env[i], '=');
		if (new)
		{
			write(1, shell->env[i], new - shell->env[i]);
			printf("=\"%s\"\n", new + 1);
		}
		else
			printf("%s\n", shell->env[i]);
=======
		equal_pos = ft_strchr(shell->env[i], '=');
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if (equal_pos)
		{
			write(STDOUT_FILENO, shell->env[i], equal_pos - shell->env[i]);
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(equal_pos + 1, STDOUT_FILENO);
			ft_putendl_fd("\"", STDOUT_FILENO);
		}
		else
			ft_putendl_fd(shell->env[i], STDOUT_FILENO);
>>>>>>> origin/5-exec
		i++;
	}
}

<<<<<<< HEAD
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
=======
static int	is_invalid_identifier(char *str, char stop_char)
{
	int	i;

	if (!str || !*str)
		return (1);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	i = 1;
	while (str[i] && str[i] != stop_char)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
>>>>>>> origin/5-exec
			return (1);
		i++;
	}
	return (0);
}

<<<<<<< HEAD
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

int		builtin_export(char **args, t_shell *shell)
{
	int exit_status;
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
=======
static int	export_without_equal(char *arg, t_shell *shell)
{
	if (is_invalid_identifier(arg, '\0'))
	{
		print_export_error(arg);
		return (1);
	}
	if (get_env_value(arg, shell) == NULL)
	{
		if (set_env_value(arg, "", shell) == 1)
			return (0);// 0 = ok
		return (1);// 1 = erreur
	}
	return (0);
}

static int	export_with_equal(char *arg, t_shell *shell)
{
	char	*equal_pos;
	char	*name;
	int		ret;

	equal_pos = ft_strchr(arg, '=');
	if (is_invalid_identifier(arg, '='))
	{
		print_export_error(arg);
		return (1);
	}
	name = ft_substr(arg, 0, equal_pos - arg);
	if (!name)
		return (1);
	ret = set_env_value(name, equal_pos + 1, shell);
	free(name);
	// set_env_value retourne 1 en succès
	if (ret == 1)
		return (0);
	return (1);
}

int	builtin_export(char **args, t_shell *shell)
{
	int	exit_status;
	int	i;
	int	func_result;

	exit_status = 0;
	if (!args[1])
	{
		print_exported_vars(shell);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
			func_result = export_with_equal(args[i], shell);
		else
			func_result = export_without_equal(args[i], shell);
		if (func_result == 1)
>>>>>>> origin/5-exec
			exit_status = 1;
		i++;
	}
	return (exit_status);
}
