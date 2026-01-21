#include "../../../includes/minishell.h"

static int	should_copy_char(char c, char *quote)
{
	if (c == '\'' || c == '\"')
	{
		if (*quote == 0)
			*quote = c;
		else if (*quote == c)
			*quote = 0;
		else
			return (1);
		return (0);
	}
	return (1);
}

char	*remove_quote(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*res;

	if (!str)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if (should_copy_char(str[i], &quote))
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}
