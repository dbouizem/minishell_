#include "../../includes/minishell.h"

static t_env	*env_array_to_list(char **envp)
{
	t_env	*head = NULL;
	t_env	*new_node;
	char	*equal_sign;
	char	*key;
	int		i = 0;
	int		len;

	while (envp && envp[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);

		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			len = equal_sign - envp[i];
			key = malloc(len + 1);
			if (key)
			{
				ft_strlcpy(key, envp[i], len + 1);
				new_node->key = key;
				new_node->value = ft_strdup(equal_sign + 1);
			}
			else
			{
				free(new_node);
				return (NULL);
			}
		}
		else
		{
			new_node->key = ft_strdup(envp[i]);
			new_node->value = NULL;
		}
		if (!new_node->key || (equal_sign && !new_node->value))
		{
			free(new_node->key);
			free(new_node);
			return (NULL);
		}
		new_node->next = head;
		head = new_node;
		i++;
	}
	return (head);
}

static void	debug_env_list(t_env *env)
{
	printf("=== Environment List ===\n");
	while (env)
	{
		printf("%s=%s\n", env->key, env->value ? env->value : "(null)");
		env = env->next;
	}
	printf("=======================\n");
}

void	init_shell(t_shell *shell, char **envp)
{
	char *term_name;

	ft_memset(shell, 0, sizeof(t_shell));
	shell->exit_status = 0;
	shell->env = NULL;
	shell->env_list = NULL;

	shell->interactive = isatty(STDIN_FILENO) && isatty(STDOUT_FILENO);
	if (shell->interactive)
	{
		if (tcgetattr(STDIN_FILENO, &shell->original_term) == -1)
		{
			perror("minishell: tcgetattr");
			exit(1);
		}
	}
	shell->env_list = env_array_to_list(envp);

	if (!shell->env_list && envp && *envp)
	{
		fprintf(stderr, "Error: Failed to initialize environment list\n");
		exit(1);
	}

	debug_env_list(shell->env_list);

	env_list_to_array(shell);

	term_name = ttyname(STDIN_FILENO);
	if (term_name)
		printf("%sTerminal: %s%s\n", CYAN, term_name, RESET);

	printf("%sâœ“ Minishell initialized successfully%s\n", GREEN, RESET);
}

static void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void	cleanup_shell(t_shell *shell)
{
	int i;

	if (shell->interactive)
	{
		if (tcsetattr(STDIN_FILENO, TCSANOW, &shell->original_term) == -1)
			perror("minishell: tcsetattr");
	}

	if (shell->env)
	{
		i = 0;
		while (shell->env[i])
		{
			free(shell->env[i]);
			i++;
		}
		free(shell->env);
		shell->env = NULL;
	}

	if (shell->env_list)
	{
		free_env_list(shell->env_list);
		shell->env_list = NULL;
	}
	rl_clear_history();
}
