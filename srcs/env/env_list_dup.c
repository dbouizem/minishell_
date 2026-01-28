/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:54:50 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/28 16:54:51 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	set_node_value(t_env *node, t_env *src)
{
	if (!src->value)
	{
		node->value = NULL;
		return (1);
	}
	node->value = ft_strdup(src->value);
	if (!check_malloc(node->value, "env_dup_value"))
		return (0);
	return (1);
}

static t_env	*create_env_dup_node(t_env *src)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!check_malloc(node, "env_dup_node"))
		return (NULL);
	node->key = ft_strdup(src->key);
	if (!check_malloc(node->key, "env_dup_key"))
	{
		free(node);
		return (NULL);
	}
	if (!set_node_value(node, src))
	{
		free(node->key);
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

static void	append_env_node(t_env **head, t_env **tail, t_env *node)
{
	if (!*head)
		*head = node;
	else
		(*tail)->next = node;
	*tail = node;
}

t_env	*dup_env_list(t_env *env_list)
{
	t_env	*head;
	t_env	*tail;
	t_env	*node;

	head = NULL;
	tail = NULL;
	while (env_list)
	{
		node = create_env_dup_node(env_list);
		if (!node)
		{
			free_env_list(head);
			return (NULL);
		}
		append_env_node(&head, &tail, node);
		env_list = env_list->next;
	}
	return (head);
}

int	print_env_list(t_env *env_list)
{
	t_shell	tmp_shell;
	int		i;

	tmp_shell.env_list = env_list;
	tmp_shell.env = NULL;
	env_list_to_array(&tmp_shell);
	if (env_list && !tmp_shell.env)
		return (1);
	i = 0;
	while (tmp_shell.env && tmp_shell.env[i])
	{
		ft_putendl_fd(tmp_shell.env[i], STDOUT_FILENO);
		i++;
	}
	free_string_array(tmp_shell.env);
	return (0);
}
