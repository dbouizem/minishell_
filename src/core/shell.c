#include "../../includes/minishell.h"

static char	**create_minimal_env(void)
{
	char	**env;
	char	cwd[1024];

	env = malloc(sizeof(char *) * 4);
	if (!env)
		return (NULL);
	if (getcwd(cwd, sizeof(cwd)))
		env[0] = ft_strjoin("PWD=", cwd);
	else
		env[0] = ft_strdup("PWD=/");
	if (!env[0])
		return (free(env), NULL);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=./minishell");
	env[3] = NULL;
	if (!env[1] || !env[2])
	{
		free(env[0]);
		free(env[1]);
		free(env[2]);
		free(env);
		return (NULL);
	}
	return (env);
}

static char	**copy_env(char **envp)
{
	char	**new_env;
	int		count;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}

static void	check_terminal(t_shell *shell)
{
	shell->interactive = isatty(STDIN_FILENO) && isatty(STDOUT_FILENO);
	if (shell->interactive)
	{
		if (tcgetattr(STDIN_FILENO, &shell->original_term) == -1)
		{
			perror("minishell: tcgetattr");
			exit(1);
		}
	}
}

void	init_shell(t_shell *shell, char **envp)
{
	char	*term_name;

	shell->exit_status = 0;
	shell->env = NULL;
	check_terminal(shell);
	term_name = ttyname(STDIN_FILENO);
	if (term_name)
		printf("%sTerminal: %s%s\n", CYAN, term_name, RESET);
	if (envp && *envp)
		shell->env = copy_env(envp);
	else
	{
		printf("%sWarning: No environment, creating minimal one%s\n",
			YELLOW, RESET);
		shell->env = create_minimal_env();
	}
	if (!shell->env)
	{
		perror("minishell: environment initialization failed");
		exit(1);
	}
}

void	cleanup_shell(t_shell *shell)
{
	int	i;

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
	rl_clear_history();
}
