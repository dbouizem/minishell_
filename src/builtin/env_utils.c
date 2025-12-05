/* #include "../includes/minishell.h"

char	*get_env_value(char *key, t_shell *shell)
{
	int		i;
	int		key_len;
	char	*value;

	if (!key || !shell || !shell->env)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, key_len) == 0
			&& shell->env[i][key_len] == '=')
		{
			value = shell->env[i] + key_len + 1;
			return (value);
		}
		i++;
	}
	return (NULL);
}

static int	count_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
		i++;
	return (i);
}

static int	update_env_value(char *key, char *value, t_shell *shell, int i)
{
	char	*new_var;
	char	*temp;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (0);
	new_var = ft_strjoin(temp, value);
	free(temp);
	if (!new_var)
		return (0);
	free(shell->env[i]);
	shell->env[i] = new_var;
	return (1);
}

static int	add_new_env(char *key, char *value, t_shell *shell)
{
	char	**new_env;
	int		count;
	int		i;
	char	*temp;
	char	*new_var;

	count = count_env(shell);
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (0);
	i = -1;
	while (++i < count)
		new_env[i] = shell->env[i];
	temp = ft_strjoin(key, "=");
	if (!temp)
		return (free(new_env), 0);
	new_var = ft_strjoin(temp, value);
	free(temp);
	if (!new_var)
		return (free(new_env), 0);
	new_env[count] = new_var;
	new_env[count + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (1);
}

int	set_env_value(char *key, char *value, t_shell *shell)
{
	int		i;
	int		key_len;

	if (!key || !shell || !shell->env)
		return (0);
	key_len = ft_strlen(key);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, key_len) == 0
			&& shell->env[i][key_len] == '=')
			return (update_env_value(key, value, shell, i));
		i++;
	}
	return (add_new_env(key, value, shell));
}

int	unset_env_value(char *key, t_shell *shell)
{
	int		i;
	int		j;
	int		key_len;
	char	**new_env;
	int		count;

	if (!key || !shell || !shell->env)
		return (0);
	key_len = ft_strlen(key);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, key_len) == 0
			&& shell->env[i][key_len] == '=')
			break ;
		i++;
	}
	if (!shell->env[i])
		return (1);
	count = count_env(shell);
	new_env = malloc(sizeof(char *) * count);
	if (!new_env)
		return (0);
	j = 0;
	for (int k = 0; k < count; k++)
	{
		if (k != i)
			new_env[j++] = shell->env[k];
		else
			free(shell->env[k]);
	}
	new_env[j] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (1);
}

 */
