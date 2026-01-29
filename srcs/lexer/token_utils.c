/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:57:12 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/28 16:57:13 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		perror("minishell: malloc");
		return (NULL);
	}
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token **current, t_token *new_token)
{
	if (!*head)
	{
		*head = new_token;
		*current = *head;
	}
	else
	{
		(*current)->next = new_token;
		*current = (*current)->next;
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	report_forbidden_char(char c)
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

int	build_tokens(char *input, t_token **head, t_token **current)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (is_forbidden_char(input[i]))
		{
			report_forbidden_char(input[i]);
			free_tokens(*head);
			return (0);
		}
		if (is_whitespace(input[i]))
			handle_spaces(input, &i, head, current);
		else if (is_special_char(input[i]))
			handle_pipe_or_redir(input, &i, head, current);
		else
			handle_word(input, &i, head, current);
	}
	return (1);
}
