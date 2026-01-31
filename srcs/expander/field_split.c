/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 12:30:00 by djh               #+#    #+#             */
/*   Updated: 2026/01/31 18:54:24 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_field_sep(char c)
{
	return (ft_isspace(c));
}

static void	update_quote_state(char c, int *in_single, int *in_double)
{
	if (c == '\'' && !*in_double)
		*in_single = !*in_single;
	else if (c == '"' && !*in_single)
		*in_double = !*in_double;
}

int	count_fields(char *str)
{
	int	i;
	int	count;
	int	in_single;
	int	in_double;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		while (str[i] && is_field_sep(str[i]))
			i++;
		if (!str[i])
			break ;
		count++;
		in_single = 0;
		in_double = 0;
		while (str[i])
		{
			update_quote_state(str[i], &in_single, &in_double);
			if (is_field_sep(str[i]) && !in_single && !in_double)
				break ;
			i++;
		}
	}
	return (count);
}

static char	*extract_field(char *str, int *i)
{
	int		start;
	int		in_single;
	int		in_double;

	while (str[*i] && is_field_sep(str[*i]))
		(*i)++;
	start = *i;
	in_single = 0;
	in_double = 0;
	while (str[*i])
	{
		update_quote_state(str[*i], &in_single, &in_double);
		if (is_field_sep(str[*i]) && !in_single && !in_double)
			break ;
		(*i)++;
	}
	return (ft_substr(str, start, *i - start));
}

char	**split_fields(char *str)
{
	char	**fields;
	int		count;
	int		i;
	int		pos;

	i = 0;
	pos = 0;
	count = count_fields(str);
	fields = malloc(sizeof(char *) * (count + 1));
	if (!check_malloc(fields, "split_fields"))
		return (NULL);
	while (i < count)
	{
		fields[i] = extract_field(str, &pos);
		if (!fields[i])
		{
			while (i > 0)
				free(fields[--i]);
			return (free(fields), NULL);
		}
		i++;
	}
	fields[count] = NULL;
	return (fields);
}
