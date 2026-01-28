/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:54:15 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/28 16:54:16 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	env_array_len(char **env)
{
	int	count;

	count = 0;
	while (env && env[count])
		count++;
	return (count);
}

static char	**copy_env_array(char **env)
{
	char	**copy;
	int		count;
	int		i;

	count = env_array_len(env);
	copy = malloc(sizeof(char *) * (count + 1));
	if (!check_malloc(copy, "export_env_copy"))
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = env[i];
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	sort_env_array(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_export_line(char *entry)
{
	char	*equal_pos;

	equal_pos = ft_strchr(entry, '=');
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	if (equal_pos)
	{
		write(STDOUT_FILENO, entry, equal_pos - entry);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(equal_pos + 1, STDOUT_FILENO);
		ft_putendl_fd("\"", STDOUT_FILENO);
	}
	else
		ft_putendl_fd(entry, STDOUT_FILENO);
}

void	print_exported_vars(t_shell *shell)
{
	int		i;
	char	**sorted_env;

	if (!shell)
		return ;
	if (!shell->env)
		env_list_to_array(shell);
	if (!shell->env)
		return ;
	sorted_env = copy_env_array(shell->env);
	if (!sorted_env)
		return ;
	sort_env_array(sorted_env);
	i = 0;
	while (sorted_env[i])
	{
		print_export_line(sorted_env[i]);
		i++;
	}
	free(sorted_env);
}
