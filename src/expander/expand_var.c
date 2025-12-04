#include "../includes/minishell.h"

char	*get_var_value(char *var_name, t_shell *shell)
{
	t_env	*env;

	if (!var_name || !*var_name)
		return (ft_strdup(""));
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(shell->exit_status));
	if (ft_strcmp(var_name, "$") == 0)
		return (ft_itoa(getpid()));
	env = shell->env_list;
	while (env)
	{
		if (env->key && ft_strcmp(env->key, var_name) == 0)
		{
			if (env->value)
				return (ft_strdup(env->value));
			else
				return (ft_strdup(""));
		}
		env = env->next;
	}
	return (ft_strdup(""));
}
