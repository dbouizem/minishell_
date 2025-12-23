#include "../../includes/minishell.h"

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

char	*process_special_var_name(char *var_name)
{
	if (ft_isdigit(var_name[0]) || var_name[0] == '-'
		|| ft_strcmp(var_name, "$$") == 0)
		return (var_name);
	if (var_name[0] == '\0')
	{
		free(var_name);
		return (ft_strdup(""));
	}
	return (NULL);
}

char	*get_var_value(char *var_name, t_shell *shell)
{
	t_env	*env;

	if (!var_name || !*var_name)
		return (ft_strdup(""));
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(shell->exit_status));
	env = shell->env_list;
	while (env)
	{
		if (env->key && ft_strcmp(env->key, var_name) == 0)
		{
			if (env->value)
				return (ft_strdup(env->value));
			else
				return (ft_strdup(""));
		}
		env = env->next;
	}
	return (ft_strdup(""));
}

char	*process_dollar(char *str, int *i, t_shell *shell)
{
	char	*var_name;
	char	*var_value;
	char	*result;

	if (!str[*i + 1] || ft_strchr(" \'\"\0", str[*i + 1]))
	{
		(*i)++;
		return (ft_strdup("$"));
	}
	var_name = extract_var_name(str, i, shell);
	if (!var_name)
		return (ft_strdup(""));
	result = process_special_var_name(var_name);
	if (result)
		return (result);
	var_value = get_var_value(var_name, shell);
	free(var_name);
	if (!var_value)
		return (ft_strdup(""));
	return (var_value);
}
