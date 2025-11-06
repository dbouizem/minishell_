#include "../includes/minishell.h"

char	*get_var_value(char *var_name, t_shell *shell)
{
	char	*value;

	(void)shell;

	if (!var_name || !*var_name)
		return (ft_strdup(""));

	value = getenv(var_name);
	if (value)
		return (ft_strdup(value));
	else
		return (ft_strdup(""));
}
