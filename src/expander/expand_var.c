#include "../includes/minishell.h"

char	*get_var_value(char *var_name, t_shell *shell)
{
	int		i;
	int		len;
	char	*value;

	if (!var_name || *var_name == '\0' || !shell || !shell->env)
		return (ft_strdup(""));

	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(shell->exit_status));

	len = ft_strlen(var_name);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var_name, len) == 0
			&& shell->env[i][len] == '=')
		{
			value = ft_strdup(shell->env[i] + len + 1);
			if (!value)
				return (ft_strdup(""));
			return (value);
		}
		i++;
	}
	return (ft_strdup(""));
}
