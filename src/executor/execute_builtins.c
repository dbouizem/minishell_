#include "../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd->args[0])
		return (1);

	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(cmd));
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (ft_cd(cmd, shell));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(cmd, shell));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(cmd, shell));
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env(shell));
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (ft_exit(cmd, shell));

	return (-1);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	if (cmd->args[1] && ft_strcmp(cmd->args[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

int	ft_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (0);
	}
	perror("pwd");
	return (1);
}

int	ft_env(t_shell *shell)
{
	t_env	*env;

	if (!shell || !shell->env_list)
		return (1);
	env = shell->env_list;
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(env->value, STDOUT_FILENO);
		}
		env = env->next;
	}
	return (0);
}

int	ft_cd(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	cwd[4096];
	char	*oldpwd;

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("cd");
		return (1);
	}
	oldpwd = ft_strdup(cwd);
	if (!cmd->args[1] || ft_strcmp(cmd->args[1], "~") == 0)
		path = get_env_value("HOME", shell);
	else if (ft_strcmp(cmd->args[1], "-") == 0)
	{
		path = get_env_value("OLDPWD", shell);
		if (path)
			printf("%s\n", path);
	}
	else
		path = cmd->args[1];
	if (!path)
	{
		ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
		free(oldpwd);
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	update_env_var("OLDPWD", oldpwd, shell);
	free(oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		update_env_var("PWD", cwd, shell);
	return (0);
}

int	ft_export(t_cmd *cmd, t_shell *shell)
{
	(void)cmd;
	(void)shell;
	return (0);
}

int	ft_unset(t_cmd *cmd, t_shell *shell)
{
	(void)cmd;
	(void)shell;
	return (0);
}

int	ft_exit(t_cmd *cmd, t_shell *shell)
{
	int	exit_code;

	printf("exit\n");
	if (cmd->args[1])
	{
		if (!ft_isnumber(cmd->args[1]))
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(cmd->args[1], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			exit_code = 2;
		}
		else if (cmd->args[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			return (1);
		}
		else
			exit_code = ft_atoi(cmd->args[1]) % 256;
	}
	else
		exit_code = shell->exit_status;
	cleanup_shell(shell);
	exit(exit_code);
}
