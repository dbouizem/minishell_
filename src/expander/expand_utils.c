#include "../../includes/minishell.h"

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	is_valid_var_start_char(char c)
{
	return (ft_isalpha(c) || c == '_');
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

char	*char_to_str(char c)
{
	char	*str;

	str = malloc(2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}
