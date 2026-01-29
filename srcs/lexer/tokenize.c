/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:57:14 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/29 02:52:58 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	process_char(char *input, int *i, t_token **head, t_token **current)
{
	if (is_whitespace(input[*i]))
		handle_spaces(input, i, head, current);
	else if (is_special_char(input[*i]))
		handle_pipe_or_redir(input, i, head, current);
	else
		handle_word(input, i, head, current);
}

static void	report_forbidden_char(char c)
{
	char	token[2];

	if (ft_isprint((unsigned char)c))
	{
		token[0] = c;
		token[1] = '\0';
		lexer_syntax_error(token);
	}
	else
		lexer_syntax_error(NULL);
}

static int	has_isolated_exclamation(t_token *head)
{
	t_token	*current;
	t_token	*last_word;

	current = head;
	last_word = NULL;
	while (current)
	{
		if (current->type == WORD)
			last_word = current;
		current = current->next;
	}
	if (last_word && ft_strcmp(last_word->value, "!") == 0)
	{
		current = last_word->next;
		while (current)
		{
			if (current->type != SPACES)
				return (0);
			current = current->next;
		}
		return (1);
	}
	return (0);
}

static int	has_invalid_token(t_token *tokens)
{
	if (has_isolated_exclamation(tokens))
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'", STDERR_FILENO);
		return (1);
	}
	while (tokens)
	{
		if (tokens->type == INVALID)
		{
			lexer_syntax_error(tokens->value);
			return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}

t_token	*tokenize(char *input)
{
	t_token	*head;
	t_token	*current;
	int		i;

	if (!input)
		return (NULL);
	if (has_quote_error(input))
		return (NULL);
	head = NULL;
	current = NULL;
	i = 0;
	while (input[i])
	{
		if (is_forbidden_char(input[i]))
		{
			report_forbidden_char(input[i]);
			free_tokens(head);
			return (NULL);
		}
		process_char(input, &i, &head, &current);
	}
	if (has_invalid_token(head))
		return (free_tokens(head), NULL);
	return (head);
}
