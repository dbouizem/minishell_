#include "../includes/minishell.h"

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
	// Cas 1: exit sans argument
	if (!args[1])
		exit(shell->exit_status);
	// Cas 2: Vérifier si l'argument est numérique
	if (!is_numeric_arg(args[1]))
	{
		print_exit_error(args[1], "numeric");
		exit(2);
	}
	// CAS SPÉCIAL : TROP D'ARGUMENTS
	if (args[2])
	{
		print_exit_error(NULL, "too_many");
		return (1);  // NE QUITTE JAMAIS, MÊME DANS UN PIPELINE !
	}
	// Cas 4: Conversion numérique
	exit_code = ft_atoll(args[1], &overflow);
	if (overflow)
	{
		print_exit_error(args[1], "numeric");
		exit(2);
	}
	exit((unsigned char)(exit_code % 256));
}
