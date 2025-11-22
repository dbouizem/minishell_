#include "../includes/minishell.h"

char	*extract_var_name(char *str, int *i)
{
	int		start;
	char	*var_name;

	(*i)++;
	start = *i;

	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	if (str[*i] == '$')
	{
		(*i)++;
		return (ft_strdup("$"));
	}
	while (str[*i] && is_valid_var_char(str[*i]))
		(*i)++;

	if (*i == start)
		return (ft_strdup("$"));

	var_name = malloc(*i - start + 1);
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, &str[start], *i - start + 1);
	return (var_name);
}

char	*process_dollar(char *str, int *i, t_shell *shell)
{
	char	*var_name;
	char	*var_value;

	if (!str[*i + 1] || str[*i + 1] == ' ' || str[*i + 1] == '\'' || str[*i + 1] == '\"')
	{
		(*i)++;
		return (ft_strdup("$"));
	}
	var_name = extract_var_name(str, i);
	if (!var_name)
		return (NULL);
	var_value = get_var_value(var_name, shell);
	free(var_name);
	return (var_value);
}
