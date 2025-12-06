#include "../includes/minishell.h"

/* Erreur variable environnement */
void	env_error(char *key, char *message)
{
	fprintf(stderr, "minishell: env: %s: %s\n", key, message);
}

/* Vérification clé valide pour variable d'environnement */
int	is_valid_env_key(char *key)
{
	int	i;

	if (!key || !*key || ft_isdigit(key[0]))
		return (0);
	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
