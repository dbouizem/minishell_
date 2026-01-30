/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:56:25 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/30 16:19:25 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*handle_quotes_dollar(char *str, int *i, t_state *state,
			t_shell *shell)
{
	if (str[*i] == '$' && !state->in_single)
	{
		if ((str[*i + 1] == '"' && str[*i + 2] == '"')
			|| (str[*i + 1] == '\'' && str[*i + 2] == '\''))
		{
			*i += 3;
			return (ft_strdup(""));
		}
		return (process_dollar(str, i, shell));
	}
	else if (str[*i] == '\'' && !state->in_double)
	{
		state->in_single = !state->in_single;
		return (char_to_str(str[(*i)++]));
	}
	else if (str[*i] == '\"' && !state->in_single)
	{
		state->in_double = !state->in_double;
		return (char_to_str(str[(*i)++]));
	}
	else if (state->in_single)
		return (extract_single_quoted_content(str, i));
	else
		return (process_normal_char(str, i, state->in_double));
}

static int	append_part(char **result, char *part)
{
	char	*new_result;

	if (!part)
		return (free(*result), 0);
	new_result = ft_strjoin_free(*result, part);
	free(part);
	if (!new_result)
		return (0);
	*result = new_result;
	return (1);
}

char	*expand_string(char *str, t_shell *shell)
{
	char	*result;
	char	*part;
	t_state	state;
	int		i;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	state = (t_state){0, 0};
	i = 0;
	while (str[i])
	{
		part = handle_quotes_dollar(str, &i, &state, shell);
		if (!append_part(&result, part))
			return (NULL);
	}
	return (result);
}
