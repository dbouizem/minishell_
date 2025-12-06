#include "../includes/minishell.h"

<<<<<<< HEAD
static int	is_number(char *str)
=======
// Cas				Afficher		Quitter ?		Code sortie
// exit				exit			Oui				Dernier status
// exit 42			exit			Oui				42
// exit hello		exit + erreur	Oui				2
// exit 1 2			exit + erreur	NON				1 (mais reste)
// exit 300			exit			Oui				44
// exit -10			exit			Oui	2			46
// Dans pipeline	exit			Oui (enfant)	Code spécifié
// echo test | exit 99

static int	is_numeric_arg(char *str)
>>>>>>> origin/5-exec
{
	int	i;

	if (!str || !*str)
		return (0);
<<<<<<< HEAD
=======

>>>>>>> origin/5-exec
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
<<<<<<< HEAD
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
=======
	long long	exit_code;
	int			overflow;

	write(STDERR_FILENO, "exit\n", 5);
	// Cas 1: exit sans argument
	if (!args[1])
		exit(shell->exit_status);
	// Cas 2: Vérifier si l'argument est numérique
	if (!is_numeric_arg(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(2);
	}
	// CAS SPÉCIAL : TROP D'ARGUMENTS
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (1);  // NE QUITTE JAMAIS, MÊME DANS UN PIPELINE !
	}
	// Cas 4: Conversion numérique
	exit_code = ft_atoll(args[1], &overflow);
	if (overflow)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(2);
	}
	exit((unsigned char)(exit_code % 256));
}
>>>>>>> origin/5-exec
