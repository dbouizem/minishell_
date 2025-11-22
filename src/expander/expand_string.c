#include "../includes/minishell.h"

char	*expand_string(char *str, t_shell *shell)
{
	char	*result;
	char	*part;
	int		i;
	int		in_single;
	int		in_double;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
		{
			in_single = !in_single;
			part = char_to_str(str[i++]);
		}
		else if (str[i] == '\"' && !in_single)
		{
			in_double = !in_double;
			part = char_to_str(str[i++]);
		}
		else if (str[i] == '$' && !in_single)
			part = process_dollar(str, &i, shell);
		else if (in_single)
			part = extract_single_quoted_content(str, &i);
		else
			part = process_normal_char(str, &i, in_double);

		if (!part)
		{
			free(result);
			return (NULL);
		}
		char *new_result = ft_strjoin_free(result, part);
		free(part);
		result = new_result;
		if (!result)
			return (NULL);
	}
	return (result);
}
