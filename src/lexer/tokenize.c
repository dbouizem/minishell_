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
	return (head);
}
