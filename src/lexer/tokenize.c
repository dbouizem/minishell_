#include "../includes/minishell.h"

t_token	*tokenize(char *input)
{
	t_token	*head;
	t_token	*current;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	if (!input)
		return (NULL);
	while (input[i])
	{
		if (is_whitespace(input[i]))
			handle_spaces(input, &i, &head, &current);
		else if (input[i] == '$')
			handle_variable(input, &i, &head, &current);
		else if (is_special_char(input[i]))
			handle_pipe_or_redir(input, &i, &head, &current);
		else
			handle_word(input, &i, &head, &current);
	}
	return (head);
}
