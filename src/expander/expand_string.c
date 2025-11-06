#include "../includes/minishell.h"

static char	*process_dollar(char *str, int *i, t_shell *shell)
{
	int		start;
	char	*var_name;
	char	*value;

	start = *i;
	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->exit_status));
	}
	if (!ft_isalpha(str[*i]) && str[*i] != '_')
		return (ft_strdup("$"));
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_substr(str, start + 1, *i - start - 1);
	if (!var_name)
		return (NULL);
	value = get_var_value(var_name, shell);
	free(var_name);
	if (!value)
		return (ft_strdup(""));
	return (value);
}

static char	*append_part(char *result, char *part)
{
	char	*temp;

	if (!result)
		return (ft_strdup(part));
	temp = ft_strjoin(result, part);
	free(result);
	return (temp);
}

char	*expand_string(char *str, t_shell *shell)
{
	char	*result;
	char	*part;
	int		i;
	int		start;

	if (!str)
		return (NULL);
	result = NULL;
	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (i > start)
			{
				part = ft_substr(str, start, i - start);
				result = append_part(result, part);
				free(part);
			}
			part = process_dollar(str, &i, shell);
			result = append_part(result, part);
			free(part);
			start = i;
		}
		else
			i++;
	}
	if (i > start)
	{
		part = ft_substr(str, start, i - start);
		result = append_part(result, part);
		free(part);
	}
	if (!result)
		return (ft_strdup(""));
	return (result);
}
