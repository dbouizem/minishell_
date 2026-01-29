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

static int	has_isolated_exclamation(t_token *head)
{
	t_token	*current;
	t_token	*last_word;
	int		word_count;

	current = head;
	last_word = NULL;
	word_count = 0;
	while (current)
	{
		if (current->type == WORD)
		{
			last_word = current;
			word_count++;
		}
		current = current->next;
	}
	if (word_count != 1 || !last_word || ft_strcmp(last_word->value, "!") != 0)
		return (0);
	current = last_word->next;
	while (current && current->type == SPACES)
		current = current->next;
	return (current == NULL);
}

static int	has_invalid_token(t_token *tokens)
{
	if (has_isolated_exclamation(tokens))
		return (1);
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

	if (!input || has_quote_error(input))
		return (NULL);
	head = NULL;
	current = NULL;
	if (!build_tokens(input, &head, &current))
		return (NULL);
	if (has_invalid_token(head))
		return (free_tokens(head), NULL);
	return (head);
}
