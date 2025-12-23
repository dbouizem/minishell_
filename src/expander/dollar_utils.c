#include "../../includes/minishell.h"

char	*handle_special_chars(char *str, int *i, t_shell *shell)
{
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->exit_status));
	}
	if (str[*i] == '$')
	{
		(*i)++;
		return (ft_strdup("$"));
	}
	return (NULL);
}

char	*extract_curly_var_name(char *str, int *i, int start)
{
	char	*var_name;

	var_name = malloc(*i - start + 1);
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, &str[start], *i - start + 1);
	return (var_name);
}

char	*handle_curly_brace_syntax(char *str, int *i, t_shell *shell)
{
	int		start;
	char	*var_name;
	char	*var_value;

	(*i)++;
	start = *i;
	while (str[*i] && str[*i] != '}')
		(*i)++;
	if (str[*i] == '}')
	{
		var_name = extract_curly_var_name(str, i, start);
		if (!var_name)
			return (NULL);
		(*i)++;
		if (ft_strcmp(var_name, "?") == 0)
		{
			free(var_name);
			return (ft_itoa(shell->exit_status));
		}
		var_value = get_var_value(var_name, shell);
		free(var_name);
		return (var_value);
	}
	*i = start - 1;
	return (ft_strdup("${"));
}

char	*handle_normal_var(char *str, int *i)
{
	int		start;
	char	*var_name;

	start = *i;
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
