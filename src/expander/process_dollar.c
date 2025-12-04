#include "../includes/minishell.h"

static char	*handle_special_chars(char *str, int *i, t_shell *shell)
{
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->exit_status));
	}
	if (str[*i] == '$')
	{
		(*i)++;
		return (ft_itoa(getpid()));
	}
	return (NULL);
}

static char	*handle_curly_brace_syntax(char *str, int *i, t_shell *shell)
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
		var_name = malloc(*i - start + 1);
		if (!var_name)
			return (NULL);
		ft_strlcpy(var_name, &str[start], *i - start + 1);
		(*i)++;
		if (ft_strcmp(var_name, "?") == 0)
		{
			free(var_name);
			return (ft_itoa(shell->exit_status));
		}
		if (ft_strcmp(var_name, "$") == 0)
		{
			free(var_name);
			return (ft_itoa(getpid()));
		}
		var_value = get_var_value(var_name, shell);
		free(var_name);
		return (var_value);
	}
	else
	{
		*i = start - 1;
		return (ft_strdup("${"));
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

char	*extract_var_name(char *str, int *i, t_shell *shell)
{
	char	*special_value;

	(*i)++;
	special_value = handle_special_chars(str, i, shell);
	if (special_value)
		return (special_value);
	if (str[*i] == '{')
		return (handle_curly_brace_syntax(str, i, shell));
	return (handle_normal_var(str, i));
}


char	*process_dollar(char *str, int *i, t_shell *shell)
{
	char	*var_name;
	char	*var_value;

	if (!str[*i + 1] || str[*i + 1] == ' '
		|| str[*i + 1] == '\'' || str[*i + 1] == '\"'
		|| str[*i + 1] == '\0')
	{
		(*i)++;
		return (ft_strdup("$"));
	}
	var_name = extract_var_name(str, i, shell);
	if (!var_name)
		return (ft_strdup(""));
	if (ft_isdigit(var_name[0]) || var_name[0] == '-'
		|| ft_strcmp(var_name, "$$") == 0)
		return (var_name);
	if (var_name[0] == '\0')
	{
		free(var_name);
		return (ft_strdup(""));
	}
	var_value = get_var_value(var_name, shell);
	free(var_name);
	if (!var_value)
		return (ft_strdup(""));
	return (var_value);
}
