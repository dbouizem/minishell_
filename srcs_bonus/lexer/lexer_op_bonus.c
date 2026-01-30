/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_op_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:58:46 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/28 16:58:47 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_ope_value(t_token_type type, char *value, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (type == OR)
			value[i] = '|';
		else if (type == AND || type == INVALID)
			value[i] = '&';
		i++;
	}
	value[len] = '\0';
}

void	create_operator_token(t_token_type type, t_token **head,
			t_token **current, int *i)
{
	char	*value;
	int		len;
	t_token	*token;

	if (type == OR || type == AND)
		len = 2;
	else
		len = 1;
	value = malloc(len + 1);
	if (!value)
		return ;
	get_ope_value(type, value, len);
	token = create_token(type, value);
	if (!token)
		return (free(value));
	add_token(head, current, token);
	*i += len ;
}

static int	find_arith_end(char *input, int start)
{
	int	j;

	j = start;
	while (input[j] && !(input[j] == ')' && input[j + 1] == ')'))
		j++;
	if (!input[j])
		return (-1);
	return (j);
}

static int	add_arith_tokens(t_token **head, t_token **current, char *trim)
{
	t_token	*first;
	t_token	*second;

	first = create_token(WORD, ft_strdup("__arith__"));
	second = create_token(WORD, trim);
	if (!first || !second)
	{
		if (first)
		{
			free(first->value);
			free(first);
		}
		free(trim);
		return (0);
	}
	add_token(head, current, first);
	add_token(head, current, second);
	return (1);
}

int	create_arith_tokens(char *input, int *i, t_token **head,
			t_token **current)
{
	char	*expr;
	char	*trim;
	int		start;
	int		j;

	start = *i + 2;
	j = find_arith_end(input, start);
	if (j == -1)
		return (0);
	expr = extract_substring(input, start, j);
	if (!expr)
		return (0);
	trim = ft_strtrim(expr, " \t\n");
	free(expr);
	if (!trim)
		return (0);
	if (!add_arith_tokens(head, current, trim))
		return (0);
	*i = j + 2;
	return (1);
}
