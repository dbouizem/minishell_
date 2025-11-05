#include "../includes/minishell.h"

void	handle_spaces(char *input, int *i, t_token **head, t_token **current)
{
	int		start;
	char	*spaces;
	t_token	*token;

	start = *i;
	while (input[*i] && is_whitespace(input[*i]))
		(*i)++;
	spaces = extract_substring(input, start, *i);
	if (spaces)
	{
		token = create_token(SPACES, spaces);
		if (token)
			add_token(head, current, token);
		else
			free(spaces);
	}
}

void	handle_variable(char *input, int *i, t_token **head, t_token **current)
{
	int		start;
	char	*var;
	t_token	*token;

	start = *i;
	(*i)++;
	if (input[*i] == '?')
		(*i)++;
	else
	{
		while (input[*i] && (input[*i] == '_'
				|| (input[*i] >= 'a' && input[*i] <= 'z')
				|| (input[*i] >= 'A' && input[*i] <= 'Z')
				|| (input[*i] >= '0' && input[*i] <= '9')))
			(*i)++;
	}
	var = extract_substring(input, start, *i);
	if (var)
	{
		token = create_token(VAR, var);
		if (token)
			add_token(head, current, token);
		else
			free(var);
	}
}

void	handle_word(char *input, int *i, t_token **head, t_token **current)
{
	int		start;
	char	*word;
	t_token	*token;

	start = *i;
	while (input[*i] && !is_whitespace(input[*i])
		&& !is_special_char(input[*i]))
	{
		if (is_quote(input[*i]))
			handle_quotes(input, i);
		else
			(*i)++;
	}
	word = extract_substring(input, start, *i);
	if (word)
	{
		token = create_token(WORD, word);
		if (token)
			add_token(head, current, token);
		else
			free(word);
	}
}
