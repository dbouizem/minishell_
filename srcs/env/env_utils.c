/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:55:09 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/28 16:55:10 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	update_existing_env(t_env *env, t_shell *shell, char *value)
{
	free(env->value);
	env->value = ft_strdup(value);
	if (!env->value)
		return (0);
	env_list_to_array(shell);
	return (1);
}

static int	init_new_env_node(t_env **node, char *key, char *value)
{
	*node = malloc(sizeof(t_env));
	if (!check_malloc(*node, "new_env_node"))
		return (0);
	(*node)->key = ft_strdup(key);
	(*node)->value = ft_strdup(value);
	if (!(*node)->key || !(*node)->value)
	{
		free((*node)->key);
		free((*node)->value);
		free(*node);
		return (0);
	}
	return (1);
}

int	update_env_var(char *key, char *value, t_shell *shell)
{
	t_env	*env;
	t_env	*new_node;

	if (!key || !shell)
		return (0);
	env = find_env_node(shell->env_list, key);
	if (env)
		return (update_existing_env(env, shell, value));
	if (!init_new_env_node(&new_node, key, value))
		return (0);
	new_node->next = shell->env_list;
	shell->env_list = new_node;
	env_list_to_array(shell);
	return (1);
}

int	set_env_value(char *key, char *value, t_shell *shell)
{
	if (!key || !shell)
		return (0);
	return (update_env_var(key, value, shell));
}

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
