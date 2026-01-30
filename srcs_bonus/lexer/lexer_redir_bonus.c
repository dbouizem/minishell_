/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:58:48 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/28 16:58:49 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell_bonus.h"

t_token_type	get_redir_type(char *input, int i)
{
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			return (HEREDOC);
		return (INPUT);
	}
	else if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			return (APPEND);
		return (TRUNC);
	}
	return (WORD);
}

static void	create_redir_token(char *input, int *i,
		t_token **head, t_token **curr)
{
	t_token_type	type;
	char			*value;
	int				len;
	t_token			*token;

	type = get_redir_type(input, *i);
	if (type == HEREDOC || type == APPEND)
		len = 2;
	else
		len = 1;
	value = extract_substring(input, *i, *i + len);
	if (!value)
		return ;
	*i += len;
	token = create_token(type, value);
	if (!token)
		free(value);
	else
		add_token(head, curr, token);
}

static void	create_pipe_token(t_token **head, t_token **current, int *i)
{
	char	*value;
	t_token	*token;

	value = malloc(2);
	if (!value)
		return ;
	value[0] = '|';
	value[1] = '\0';
	token = create_token(PIPE, value);
	if (token)
		add_token(head, current, token);
	else
		free(value);
	(*i)++;
}

static void	create_paren_token(char *input, int *i,
		t_token **head, t_token **current)
{
	t_token	*token;

	if (input[*i] == '(' && input[*i + 1] == '(')
	{
		if (!create_arith_tokens(input, i, head, current))
		{
			token = create_token(PAREN_OPEN, ft_strdup("("));
			if (!token)
				return ;
			add_token(head, current, token);
			(*i)++;
		}
		return ;
	}
	if (input[*i] == '(')
		token = create_token(PAREN_OPEN, ft_strdup("("));
	else
		token = create_token(PAREN_CLOSE, ft_strdup(")"));
	if (!token)
		return ;
	add_token(head, current, token);
	(*i)++;
}

void	handle_pipe_or_redir(char *input, int *i,
		t_token **head, t_token **current)
{
	if (input[*i] == '|')
	{
		if (input[*i + 1] == '|')
			create_operator_token(OR, head, current, i);
		else
			create_pipe_token(head, current, i);
	}
	else if (input[*i] == '&')
	{
		if (input[*i + 1] == '&')
			create_operator_token(AND, head, current, i);
		else
			create_operator_token(INVALID, head, current, i);
	}
	else if (input[*i] == '(' || input[*i] == ')')
		create_paren_token(input, i, head, current);
	else
		create_redir_token(input, i, head, current);
}
