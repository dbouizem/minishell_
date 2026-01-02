#include "../includes/minishell.h"

int	count_env_nodes(t_env *env_list)
{
	int	count;

	count = 0;
	while (env_list)
	{
		count++;
		env_list = env_list->next;
	}
	return (count);
}

static void	free_env_array(char **env_array)
{
	int	i;

	if (!env_array)
		return ;
	i = 0;
	while (env_array[i])
		free(env_array[i++]);
	free(env_array);
}

static char	*create_env_entry(t_env *env)
{
	char	*entry;

	if (env->value)
		entry = ft_strjoin3(env->key, "=", env->value);
	else
		entry = ft_strjoin(env->key, "=");
	return (entry);
}

static int	build_env_array(t_shell *shell, char **env_array)
{
	t_env	*env;
	int		i;
	char	*entry;

	i = 0;
	env = shell->env_list;
	while (env)
	{
		entry = create_env_entry(env);
		if (!entry)
		{
			while (i-- > 0)
				free(env_array[i]);
			return (0);
		}
		env_array[i] = entry;
		i++;
		env = env->next;
	}
	env_array[i] = NULL;
	return (1);
}

void	env_list_to_array(t_shell *shell)
{
	char	**env_array;

	if (!shell)
		return ;
	if (shell->env)
		free_env_array(shell->env);
	env_array = malloc(sizeof(char *) * (count_env_nodes(shell->env_list) + 1));
	if (!check_malloc(env_array, "env_array"))
	{
		shell->env = NULL;
		return ;
	}
	if (!build_env_array(shell, env_array))
	{
		free(env_array);
		shell->env = NULL;
		return ;
	}
	shell->env = env_array;
}
