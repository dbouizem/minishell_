#include "../../includes/minishell.h"

/* Erreur fatale du shell */
void	shell_error(char *message, int exit_code)
{
	fprintf(stderr, "minishell: error: %s\n", message);
	exit(exit_code);
}

/* Erreur de traitement */
void	process_error(char *context, t_shell *shell)
{
	fprintf(stderr, "minishell: %s\n", context);
	if (shell)
		shell->exit_status = 1;
}

/* Vérification allocation mémoire */
void	*check_malloc(void *ptr, char *context)
{
	if (!ptr)
	{
		fprintf(stderr, "minishell: %s %s\n",
			"memory allocation failed for", context);
		return (NULL);
	}
	return (ptr);
}
