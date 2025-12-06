#include "../includes/minishell.h"

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
			return (1);
		i++;
	}
	return (0);
}

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
}
