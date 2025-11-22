#include "../includes/minishell.h"

char	*extract_substring(char *input, int start, int end)
{
	char	*str;
	int		len;
	int		i;

	len = end - start;
	if (len <= 0)
		return (NULL);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = input[start++];
	str[i] = '\0';
	return (str);
}

int	handle_quotes(char *input, int *i)
{
	char	quote_type;

	quote_type = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote_type)
		(*i)++;
	if (!input[*i])
	{
		printf("minishell: unclosed quote `%c'\n", quote_type);
		return (0);
	}
	(*i)++;
	return (1);
}
