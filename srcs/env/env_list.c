#include "../../includes/minishell.h"

static t_env	*create_node(char *env_entry)
{
	t_env	*node;
	char	*equal_sign;

	node = malloc(sizeof(t_env));
	if (!check_malloc(node, "env_node"))
		return (NULL);
	equal_sign = ft_strchr(env_entry, '=');
	if (equal_sign)
	{
		node->key = ft_substr(env_entry, 0, equal_sign - env_entry);
		node->value = ft_strdup(equal_sign + 1);
	}
	else
	{
		node->key = ft_strdup(env_entry);
		node->value = NULL;
	}
	return (node);
}

static int	validate_node(t_env *node, char *env_entry)
{
	char	*equal_sign;

	equal_sign = ft_strchr(env_entry, '=');
	if (!node->key)
		return (0);
	if (equal_sign && !node->value)
		return (0);
	return (1);
}

static void	cleanup_node(t_env *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}

t_env	*env_array_to_list(char **envp)
{
	t_env	*head;
	t_env	*node;
	int		i;

	head = NULL;
	i = 0;
	while (envp && envp[i])
	{
		node = create_node(envp[i]);
		if (!node)
			return (free_env_list(head), NULL);
		if (!validate_node(node, envp[i]))
		{
			cleanup_node(node);
			return (free_env_list(head), NULL);
		}
		node->next = head;
		head = node;
		i++;
	}
	return (head);
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}
