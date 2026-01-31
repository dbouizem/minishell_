/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djh <djh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 12:30:00 by djh               #+#    #+#             */
/*   Updated: 2026/01/31 12:30:00 by djh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_partial(char **array, int count)
{
	while (count > 0)
		free(array[--count]);
	free(array);
}

static int	count_total_fields(char **args)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (args && args[i])
		total += count_fields(args[i++]);
	return (total);
}

static char	**build_split_args(char **args, int total)
{
	char	**new_args;
	char	**fields;
	int		i;
	int		j;
	int		k;

	new_args = malloc(sizeof(char *) * (total + 1));
	if (!check_malloc(new_args, "split_args"))
		return (NULL);
	i = 0;
	k = 0;
	while (args[i])
	{
		fields = split_fields(args[i++]);
		if (!fields)
			return (free_partial(new_args, k), NULL);
		j = 0;
		while (fields[j])
			new_args[k++] = fields[j++];
		free(fields);
	}
	new_args[k] = NULL;
	return (new_args);
}

void	split_command_args(t_cmd *cmd)
{
	char	**new_args;
	int		total;

	if (!cmd || !cmd->args)
		return ;
	total = count_total_fields(cmd->args);
	if (total == 0)
	{
		free_string_array(cmd->args);
		cmd->args = NULL;
		return ;
	}
	new_args = build_split_args(cmd->args, total);
	if (!new_args)
		return ;
	free_string_array(cmd->args);
	cmd->args = new_args;
}
