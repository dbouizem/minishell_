#include "../includes/minishell.h"

static char	*handle_special_chars(char *str, int *i)
{
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
	return (NULL);
}

static char	*handle_curly_brace_syntax(char *str, int *i)
{
	int		start;
	char	*var_name;

	(*i)++;
	start = *i;
	while (str[*i] && str[*i] != '}')
		(*i)++;
	if (str[*i] == '}')
	{
		var_name = malloc(*i - start + 1);
		if (!var_name)
			return (NULL);
		ft_strlcpy(var_name, &str[start], *i - start + 1);
		(*i)++;
		return (var_name);
	}
	else
	{
		*i = start - 1;
		return (ft_strdup("$"));
	}
}

static char	*handle_normal_var(char *str, int *i)
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

char	*extract_var_name(char *str, int *i)
{
	char	*special_char;

	(*i)++;
	special_char = handle_special_chars(str, i);
	if (special_char)
		return (special_char);
	if (str[*i] == '{')
		return (handle_curly_brace_syntax(str, i));
	return (handle_normal_var(str, i));
}

char	*process_dollar(char *str, int *i, t_shell *shell)
{
	char	*var_name;
	char	*var_value;

	if (!str[*i + 1] || str[*i + 1] == ' '
		|| str[*i + 1] == '\'' || str[*i + 1] == '\"')
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
