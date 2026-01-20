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

static int	has_invalid_token(t_token *tokens)
{
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
		process_char(input, &i, &head, &current);
	if (has_invalid_token(head))
	{
		free_tokens(head);
		return (NULL);
	}
	return (head);
}
