#include "../includes/minishell.h"

<<<<<<< HEAD
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
=======
static int	is_invalid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (1);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
>>>>>>> origin/5-exec
			return (1);
		i++;
	}
	return (0);
}

<<<<<<< HEAD
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
=======
static void	print_unset_error(char *arg)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

int	builtin_unset(char **args, t_shell *shell)
{
	int	i;
	int	has_error;

	if (!args[1])
		return (0);
	has_error = 0;
	i = 1;
	while (args[i])
	{
		if (is_invalid_identifier(args[i]))
		{
			print_unset_error(args[i]);
			has_error = 1;
		}
		else
			unset_env_value(args[i], shell);// Supprime même si variable n'existe pas (pas d'erreur)
		i++;
	}
	return (has_error);  // 0 = tout OK, 1 = au moins une erreur
>>>>>>> origin/5-exec
}
