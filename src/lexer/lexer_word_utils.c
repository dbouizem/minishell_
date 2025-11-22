#include "../includes/minishell.h"

static char	*handle_quoted_part(char *input, int *i,
		char quote_type, int *has_content)
{
	char	*part;
	int		start;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != quote_type)
		(*i)++;
	if (!input[*i])
		return (NULL);
	part = extract_substring(input, start, *i);
	(*i)++;
	*has_content = 1;
	return (part);
}

static char	*handle_normal_part(char *input, int *i, int *has_content)
{
	char	*part;
	int		start;

	start = *i;
	while (input[*i] && !is_whitespace(input[*i])
		&& !is_special_char(input[*i]) && !is_quote(input[*i]))
		(*i)++;
	part = extract_substring(input, start, *i);
	if (part && ft_strlen(part) > 0)
		*has_content = 1;
	return (part);
}

static char	*process_word_part(char *input, int *i, int *has_content)
{
	char	*part;

	if (is_quote(input[*i]))
		part = handle_quoted_part(input, i, input[*i], has_content);
	else
		part = handle_normal_part(input, i, has_content);
	return (part);
}

static char	*concat_parts(char *result, char *part)
{
	char	*temp;

	if (!part)
	{
		free(result);
		return (NULL);
	}
	temp = ft_strjoin(result, part);
	free(result);
	free(part);
	return (temp);
}

char	*extract_word_without_quotes(char *input, int *i)
{
	char	*result;
	char	*part;
	int		has_content;

	result = ft_strdup("");
	has_content = 0;
	if (!result)
		return (NULL);
	while (input[*i] && !is_whitespace(input[*i])
		&& !is_special_char(input[*i]))
	{
		part = process_word_part(input, i, &has_content);
		result = concat_parts(result, part);
		if (!result)
			return (NULL);
	}
	if (!has_content && result && ft_strlen(result) == 0)
	{
		if (*i > 0 && is_quote(input[*i - 1]))
			return (result);
		free(result);
		return (NULL);
	}
	return (result);
}
