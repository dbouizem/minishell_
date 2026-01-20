#include "../../includes/minishell.h"

static char	*handle_quoted_part(char *input, int *i, char quote_type)
{
	char	*part;
	int		start;

	start = *i;
	(*i)++;
	while (input[*i] && input[*i] != quote_type)
		(*i)++;
	if (!input[*i])
		return (NULL);
	(*i)++;
	part = extract_substring(input, start, *i);
	return (part);
}

static char	*handle_normal_part(char *input, int *i)
{
	char	*part;
	int		start;

	start = *i;
	while (input[*i] && !is_whitespace(input[*i])
		&& !is_special_char(input[*i]) && !is_quote(input[*i]))
	{
		if (is_forbidden_char(input[*i]))
			break ;
		(*i)++;
	}
	part = extract_substring(input, start, *i);
	return (part);
}

static char	*process_word_part(char *input, int *i)
{
	char	*part;

	if (is_quote(input[*i]))
		part = handle_quoted_part(input, i, input[*i]);
	else
		part = handle_normal_part(input, i);
	return (part);
}

char	*extract_word_without_quotes(char *input, int *i)
{
	char	*result;
	char	*part;
	char	*temp;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (input[*i] && !is_whitespace(input[*i])
		&& !is_special_char(input[*i]) && !is_forbidden_char(input[*i]))
	{
		part = process_word_part(input, i);
		if (!part)
		{
			free(result);
			return (NULL);
		}
		temp = ft_strjoin(result, part);
		free(result);
		free(part);
		result = temp;
		if (!result)
			return (NULL);
	}
	return (result);
}
