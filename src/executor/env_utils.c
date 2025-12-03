#include "../includes/minishell.h"

void	env_list_to_array(t_shell *shell)
{
	t_env	*env;
	int		count;
	int		i;
	char	*temp;

	if (!shell)
		return ;

	if (shell->env)
	{
		i = 0;
		while (shell->env[i])
		{
			free(shell->env[i]);
			i++;
		}
		free(shell->env);
	}
	count = 0;
	env = shell->env_list;
	while (env)
	{
		count++;
		env = env->next;
	}
	shell->env = malloc(sizeof(char *) * (count + 1));
	if (!shell->env)
		return ;
	i = 0;
	env = shell->env_list;
	while (env)
	{
		if (env->value)
		{
			temp = ft_strjoin3(env->key, "=", env->value);
			shell->env[i] = temp;
		}
		else
			shell->env[i] = ft_strdup(env->key);
		i++;
		env = env->next;
	}
	shell->env[i] = NULL;
}

char *get_env_value(char *key, t_shell *shell)
{
	t_env *env;

	if (!key || !shell)
	{
		printf("[DEBUG] get_env_value: key or shell is NULL\n");
		return (NULL);
	}
	if (!shell->env_list)
	{
		printf("[DEBUG] get_env_value: env_list is NULL\n");
		return (NULL);
	}
	printf("[DEBUG] get_env_value: Looking for '%s'\n", key);
	env = shell->env_list;
	while (env)
	{
		if (!env->key)
		{
			env = env->next;
			continue ;
		}
		if (ft_strcmp(env->key, key) == 0)
		{
			printf("[DEBUG] get_env_value: Found '%s'='%s'\n",
				key, env->value ? env->value : "(null)");
			return (env->value);
		}
		env = env->next;
	}
	printf("[DEBUG] get_env_value: '%s' not found\n", key);
	return (NULL);
}

void	update_env_var(char *key, char *value, t_shell *shell)
{
	t_env	*env;
	t_env	*new_node;

	if (!key || !shell)
		return ;
	env = shell->env_list;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			env_list_to_array(shell);
			return ;
		}
		env = env->next;
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = shell->env_list;
	shell->env_list = new_node;
	env_list_to_array(shell);
}
