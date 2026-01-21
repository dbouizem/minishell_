#include "../../includes/minishell.h"

char	*get_env_value(char *key, t_shell *shell)
{
	t_env	*env;

	if (!key || !shell)
		return (NULL);
	env = shell->env_list;
	while (env)
	{
		if (env->key && ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
