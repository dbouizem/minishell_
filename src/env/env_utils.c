#include "../includes/minishell.h"

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

static t_env	*find_env_node(t_env *env_list, char *key)
{
	t_env	*env;

	env = env_list;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	update_env_var(char *key, char *value, t_shell *shell)
{
	t_env	*env;
	t_env	*new_node;

	if (!key || !shell)
		return ;
	env = find_env_node(shell->env_list, key);
	if (env)
	{
		free(env->value);
		env->value = ft_strdup(value);
		env_list_to_array(shell);
		return ;
	}
	new_node = malloc(sizeof(t_env));
	if (!check_malloc(new_node, "new_env_node"))
		return ;
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = shell->env_list;
	shell->env_list = new_node;
	env_list_to_array(shell);
}

int	set_env_value(char *key, char *value, t_shell *shell)
{
	if (!key || !shell)
		return (0);
	update_env_var(key, value, shell);
	return (1);
}

int	unset_env_value(char *key, t_shell *shell)
{
	t_env	*prev;
	t_env	*curr;

	if (!key || !shell || !shell->env_list)
		return (0);
	prev = NULL;
	curr = shell->env_list;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				shell->env_list = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			env_list_to_array(shell);
			return (1);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}
