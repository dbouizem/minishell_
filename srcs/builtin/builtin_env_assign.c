/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_assign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:54:08 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/28 16:54:09 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	append_env_node(t_env **env_list, t_env *node)
{
	t_env	*tail;

	if (!*env_list)
	{
		*env_list = node;
		return ;
	}
	tail = *env_list;
	while (tail->next)
		tail = tail->next;
	tail->next = node;
}

static int	set_env_in_list(t_env **env_list, char *key, char *value)
{
	t_env	*node;

	node = find_env_node(*env_list, key);
	if (node)
	{
		free(node->value);
		node->value = value;
		free(key);
		return (node->value != NULL);
	}
	node = malloc(sizeof(t_env));
	if (!check_malloc(node, "env_new_node"))
	{
		free(key);
		free(value);
		return (0);
	}
	node->key = key;
	node->value = value;
	node->next = NULL;
	append_env_node(env_list, node);
	return (1);
}

static int	extract_env_assignment(char *arg, char **key, char **value)
{
	char	*equal_pos;

	equal_pos = ft_strchr(arg, '=');
	if (!equal_pos)
		return (0);
	if (equal_pos == arg)
		return (-2);
	*key = ft_substr(arg, 0, equal_pos - arg);
	if (!check_malloc(*key, "env_key"))
		return (-1);
	if (!is_valid_env_key(*key))
	{
		free(*key);
		return (-2);
	}
	*value = ft_strdup(equal_pos + 1);
	if (!check_malloc(*value, "env_value"))
	{
		free(*key);
		return (-1);
	}
	return (1);
}

int	apply_env_assignment(t_env **env_list, char *arg)
{
	char	*key;
	char	*value;
	int		ret;

	key = NULL;
	value = NULL;
	ret = extract_env_assignment(arg, &key, &value);
	if (ret == 0)
		return (0);
	if (ret == -2)
	{
		env_error(arg, "not a valid identifier");
		return (-1);
	}
	if (ret == -1)
		return (-1);
	if (!set_env_in_list(env_list, key, value))
		return (-1);
	return (1);
}
