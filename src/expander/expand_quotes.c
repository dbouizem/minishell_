#include "../includes/minishell.h"

char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;
	int		in_quote;
	char	quote_char;

	if (!str)
		return (NULL);
	result = malloc(strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_quote = 0;
	quote_char = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && !in_quote)
		{
			in_quote = 1;
			quote_char = str[i];
			i++;
			continue ;
		}
		if (str[i] == quote_char && in_quote)
		{
			in_quote = 0;
			i++;
			continue ;
		}
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

int	is_in_quotes(char *str, int pos)
{
	int		i;
	int		in_single;
	int		in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (i < pos)
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		i++;
	}
	return (in_single || in_double);
}
