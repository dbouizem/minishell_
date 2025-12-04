#include "../includes/minishell.h"

static void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char *find_command_path(char *cmd, t_shell *shell)
{
	char	*path;
	char	*full_path;
	char	**paths;
	int		i;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path = get_env_value("PATH", shell);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin3(paths[i], "/", cmd);
		if (!full_path)
		{
			i++;
			continue ;
		}
		if (access(full_path, F_OK) == 0)
		{
			free_string_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_string_array(paths);
	return (NULL);
}

// Dans execute_external.c
void	handle_exec_error(char *cmd, t_shell *shell)
{
	struct stat	path_stat;

	if (ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putendl_fd(": Is a directory", STDERR_FILENO);
			shell->exit_status = 126;
		}
		else if (access(cmd, F_OK) != 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
			shell->exit_status = 127;
		}
		else if (access(cmd, X_OK) != 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putendl_fd(": Permission denied", STDERR_FILENO);
			shell->exit_status = 126;
		}
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		shell->exit_status = 127;
	}
}

void	execute_external_no_fork(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_path;

	if (!cmd || !cmd->args || !cmd->args[0])
		exit(1);
	cmd_path = find_command_path(cmd->args[0], shell);
	if (!cmd_path)
	{
		handle_exec_error(cmd->args[0], shell);
		exit(shell->exit_status);
	}
	env_list_to_array(shell);

	execve(cmd_path, cmd->args, shell->env);

	perror("execve");
	free(cmd_path);
	exit(127);
}

int	execute_external(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	cmd_path = find_command_path(cmd->args[0], shell);
	if (!cmd_path)
	{
		handle_exec_error(cmd->args[0], shell);
		return (shell->exit_status);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		shell->exit_status = 1;
		return (1);
	}

	if (pid == 0)
	{
		env_list_to_array(shell);
		execve(cmd_path, cmd->args, shell->env);

		perror("execve");
		free(cmd_path);
		exit(127);
	}
	else
	{
		free(cmd_path);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			shell->exit_status = WEXITSTATUS(status);
			return (shell->exit_status);
		}
		else
		{
			shell->exit_status = 1;
			return (1);
		}
	}
}
