#include "../includes/minishell.h"

char	*get_var_value(char *var_name, t_shell *shell)
{
	char	*value;

	if (!var_name || !*var_name)
		return (ft_strdup(""));
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(shell->exit_status));
	if (ft_strcmp(var_name, "$") == 0)
		return (ft_itoa(getpid()));
	value = getenv(var_name);
	if (value)
		return (ft_strdup(value));
	else
		return (ft_strdup(""));
}
