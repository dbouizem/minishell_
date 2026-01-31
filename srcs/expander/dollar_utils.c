/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:56:20 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/28 16:56:21 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_special_chars(char *str, int *i, t_shell *shell)
{
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->exit_status));
	}
	return (NULL);
}

char	*extract_curly_var_name(char *str, int *i, int start)
{
	char	*var_name;

	var_name = malloc(*i - start + 1);
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, &str[start], *i - start + 1);
	return (var_name);
}

char	*handle_curly_brace_syntax(char *str, int *i, t_shell *shell)
{
	int		start;
	char	*var_name;

	(void)shell;
	(*i)++;
	start = *i;
	while (str[*i] && str[*i] != '}')
		(*i)++;
	if (str[*i] == '}')
	{
		var_name = extract_curly_var_name(str, i, start);
		if (!var_name)
			return (NULL);
		(*i)++;
		return (var_name);
	}
	*i = start - 1;
	return (ft_strdup("${"));
}

char	*handle_normal_var(char *str, int *i)
{
	int		start;
	char	*var_name;

	start = *i;
	while (str[*i] && is_valid_var_char(str[*i]))
		(*i)++;
	if (*i == start)
		return (ft_strdup("$"));
	var_name = malloc(*i - start + 1);
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, &str[start], *i - start + 1);
	return (var_name);
}

char	*handle_dollar_basic_cases(char *str, int *i)
{
	if (!str[*i + 1])
		return ((*i)++, ft_strdup("$"));
	if (str[*i + 1] == '"' || str[*i + 1] == '\'')
		return ((*i)++, ft_strdup(""));
	if (str[*i + 1] == ' ')
		return ((*i)++, ft_strdup("$"));
	return (NULL);
}
