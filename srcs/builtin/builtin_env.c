#include "../../includes/minishell.h"

void	print_env(t_shell *shell)
{
	int	i;

	if (!shell || !shell->env)
		return ;
	i = 0;
	while (shell->env[i])
	{
		ft_putendl_fd(shell->env[i], STDOUT_FILENO);
		i++;
	}
}

static int	init_env_context(t_shell *shell, char **args,
				int *i, t_env **tmp_env)
{
	*i = 1;
	if (args[*i] && ft_strcmp(args[*i], "-i") == 0)
	{
		*tmp_env = NULL;
		(*i)++;
		return (0);
	}
	*tmp_env = dup_env_list(shell->env_list);
	if (shell->env_list && !*tmp_env)
	{
		shell->exit_status = 1;
		return (1);
	}
	return (0);
}

static int	apply_env_assignments(t_env **env_list, char **args, int *i)
{
	int	ret;

	while (args[*i] && ft_strchr(args[*i], '='))
	{
		ret = apply_env_assignment(env_list, args[*i]);
		if (ret != 1)
			return (1);
		(*i)++;
	}
	return (0);
}

static int	env_execute(t_shell *shell, t_env *tmp_env, char **args, int i)
{
	t_shell	tmp_shell;
	t_cmd	cmd;
	int		status;

	if (!args[i])
		return (print_env_list(tmp_env));
	cmd.args = &args[i];
	cmd.redirs = NULL;
	cmd.next = NULL;
	tmp_shell = *shell;
	tmp_shell.env_list = tmp_env;
	tmp_shell.env = NULL;
	status = execute_external(&cmd, &tmp_shell);
	if (tmp_shell.env)
		free_string_array(tmp_shell.env);
	shell->exit_status = tmp_shell.exit_status;
	return (status);
}

int	builtin_env(char **args, t_shell *shell)
{
	t_env	*tmp_env;
	int		i;
	int		status;

	if (!shell)
		return (1);
	if (!args[1])
	{
		print_env(shell);
		return (0);
	}
	if (init_env_context(shell, args, &i, &tmp_env) != 0)
		return (1);
	if (apply_env_assignments(&tmp_env, args, &i) != 0)
	{
		free_env_list(tmp_env);
		shell->exit_status = 1;
		return (1);
	}
	status = env_execute(shell, tmp_env, args, i);
	free_env_list(tmp_env);
	shell->exit_status = status;
	return (status);
}
