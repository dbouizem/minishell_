#include "../includes/minishell.h"

static int	has_quote_error(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (is_quote(input[i]))
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				i++;
			if (!input[i])
			{
				printf("minishell: syntax error: unclosed quote `%c'\n", quote);
				return (1);
			}
			i++;
		}
		else
			i++;
	}
	return (0);
}

static void	process_char(char *input, int *i, t_token **head, t_token **current)
{
	if (is_whitespace(input[*i]))
		handle_spaces(input, i, head, current);
	else if (is_special_char(input[*i]))
		handle_pipe_or_redir(input, i, head, current);
	else if (is_forbidden_char(input[*i]))
		handle_invalid_char(input, i, head, current);
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
