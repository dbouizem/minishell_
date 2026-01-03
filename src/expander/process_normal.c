#include "../includes/minishell.h"

char	*extract_single_quoted_content(char *str, int *i)
{
	int		start;
	char	*result;

	start = *i;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (*i == start)
		return (NULL);
	result = malloc(*i - start + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, &str[start], *i - start + 1);
	return (result);
}

char	*process_normal_char(char *str, int *i, int in_double_quotes)
{
	int		start;
	char	*result;

	start = *i;
	(void)in_double_quotes;
	while (str[*i] && str[*i] != '$' && str[*i] != '\'' && str[*i] != '\"')
		(*i)++;
	if (*i == start)
		return (char_to_str(str[(*i)++]));
	result = malloc(*i - start + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, &str[start], *i - start + 1);
	return (result);
}
