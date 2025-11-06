#include "../includes/minishell.h"

char	*process_dollar(char *str, int *i, t_shell *shell)
{
	char	*var_name;
	char	*var_value;
	int		start;

	(*i)++;
	if (!str[*i] || str[*i] == ' ' || str[*i] == '\"' || str[*i] == '\'')
		return (ft_strdup("$"));
	start = *i;
	while (str[*i] && is_valid_var_char(str[*i]))
		(*i)++;
	if (*i == start)
		return (ft_strdup(""));
	var_name = ft_substr(str, start, *i - start);
	if (!var_name)
		return (NULL);
	var_value = get_var_value(var_name, shell);
	free(var_name);
	return (var_value);
}

char	*expand_string(char *str, t_shell *shell)
{
	char	*result;
	char	*temp;
	char	*new_result;
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
			i++;
			continue ;
		}
		if (str[i] == '\"' && !in_single)
		{
			in_double = !in_double;
			i++;
			continue ;
		}
		if (str[i] == '$' && !in_single)
		{
			temp = process_dollar(str, &i, shell);
			if (temp)
			{
				new_result = ft_strjoin(result, temp);
				free(result);
				free(temp);
				result = new_result;
				if (!result)
					return (NULL);
			}
		}
		else
		{
			temp = char_to_str(str[i]);
			if (temp)
			{
				new_result = ft_strjoin(result, temp);
				free(result);
				free(temp);
				result = new_result;
				if (!result)
					return (NULL);
			}
			i++;
		}
	}
	return (result);
}
