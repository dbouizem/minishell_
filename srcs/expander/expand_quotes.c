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

static int	copy_masked_quote(char c, char *result, int *j)
{
	if (c == EXP_QUOTE_SQ)
	{
		result[(*j)++] = '\'';
		return (1);
	}
	if (c == EXP_QUOTE_DQ)
	{
		result[(*j)++] = '\"';
		return (1);
	}
	return (0);
}

static void	init_remove_state(int *i, int *j, t_state *state)
{
	*i = 0;
	*j = 0;
	state->in_single = 0;
	state->in_double = 0;
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
	init_remove_state(&i, &j, &state);
	while (str[i])
	{
		if (copy_masked_quote(str[i], result, &j))
			i++;
		else if (handle_quotes_flags(str[i], &state))
			i++;
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
