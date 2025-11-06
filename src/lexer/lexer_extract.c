#include "../includes/minishell.h"

char	*extract_substring(char *input, int start, int end)
{
	char	*str;
	int		len;
	int		i;

	len = end - start;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = input[start++];
	str[i] = '\0';
	if (i > 0 && str[i - 1] == '\n')
		str[i - 1] = '\0';
	return (str);
}

void	handle_quotes(char *input, int *i)
{
	char	quote;

	quote = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] == quote)
		(*i)++;
}
