#include "../includes/minishell.h"

char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;
	int		in_single;
	int		in_double;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
		{
			in_single = !in_single;
			i++;
			continue ;
		}
		else if (str[i] == '\"' && !in_single)
		{
			in_double = !in_double;
			i++;
			continue ;
		}
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

char	*clean_quotes(char *str)
{
	char	*result;

	if (!str)
		return (NULL);
	result = remove_quotes(str);
	free(str);
	return (result);
}
