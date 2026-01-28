/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:56:22 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/28 16:56:23 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_quotes_flags(char c, t_state *state)
{
	if (c == '\'' && !state->in_double)
	{
		state->in_single = !state->in_single;
		return (1);
	}
	else if (c == '\"' && !state->in_single)
	{
		state->in_double = !state->in_double;
		return (1);
	}
	return (0);
}

char	*remove_quotes(char *str)
{
	char		*result;
	int			i;
	int			j;
	t_state		state;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	state.in_single = 0;
	state.in_double = 0;
	while (str[i])
	{
		if (handle_quotes_flags(str[i], &state))
		{
			i++;
			continue ;
		}
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
