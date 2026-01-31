/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_delim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 00:55:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/31 00:55:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	should_skip_dollar(char *str, int i)
{
	if (str[i] != '$')
		return (0);
	if (str[i + 1] != '\'' && str[i + 1] != '"')
		return (0);
	return (i == 0 || str[i - 1] != '$');
}

static char	*init_delim_copy(char *str, int *i, int *j, t_state *state)
{
	char	*result;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	*i = 0;
	*j = 0;
	*state = (t_state){0, 0};
	return (result);
}

char	*remove_heredoc_delimiter(char *str)
{
	char	*result;
	int		i;
	int		j;
	t_state	state;

	result = init_delim_copy(str, &i, &j, &state);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (should_skip_dollar(str, i))
			i++;
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
