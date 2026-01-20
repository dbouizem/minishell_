/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:05:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/21 21:05:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	append_arg_bonus(char ***dst, int *count, char *value)
{
	char	**new_args;
	int		i;

	if (!value)
		return (0);
	new_args = malloc(sizeof(char *) * (*count + 2));
	if (!new_args)
	{
		free(value);
		return (0);
	}
	i = 0;
	while (i < *count)
	{
		new_args[i] = (*dst)[i];
		i++;
	}
	new_args[*count] = value;
	new_args[*count + 1] = NULL;
	free(*dst);
	*dst = new_args;
	(*count)++;
	return (1);
}

int	append_array_bonus(char ***dst, int *count,
			char **arr, int arr_count)
{
	char	**new_args;

	if (arr_count == 0)
	{
		free(arr);
		return (1);
	}
	new_args = malloc(sizeof(char *) * (*count + arr_count + 1));
	if (!new_args)
	{
		ft_free_tab(arr);
		return (0);
	}
	if (*count)
		ft_memcpy(new_args, *dst, sizeof(char *) * (*count));
	if (arr_count)
		ft_memcpy(new_args + *count, arr, sizeof(char *) * arr_count);
	new_args[*count + arr_count] = NULL;
	free(*dst);
	free(arr);
	*dst = new_args;
	*count += arr_count;
	return (1);
}

int	append_literal_bonus(char ***dst, int *count,
			char *pattern, char *mask)
{
	free(mask);
	return (append_arg_bonus(dst, count, pattern));
}

void	sort_strings_bonus(char **arr, int count)
{
	int		i;
	int		swapped;
	char	*tmp;

	if (!arr || count < 2)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i + 1 < count)
		{
			if (ft_strcmp(arr[i], arr[i + 1]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
				swapped = 1;
			}
			i++;
		}
	}
}
