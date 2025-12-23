#include "../../includes/minishell.h"

char	*search_in_paths(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin3(paths[i], "/", cmd);
		if (full_path && access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, t_shell *shell)
{
	char	*full_path;
	char	**paths;

	if (ft_strchr(cmd, '/'))
		return (handle_absolute_path(cmd));
	if (!get_env_value("PATH", shell))
		return (NULL);
	paths = ft_split(get_env_value("PATH", shell), ':');
	if (!paths)
		return (NULL);
	full_path = search_in_paths(paths, cmd);
	free_string_array(paths);
	return (full_path);
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
	pid = fork_process();
	if (pid == 0)
	{
		env_list_to_array(shell);
		execve(cmd_path, cmd->args, shell->env);
		handle_execve_error(cmd_path);
	}
	else
	{
		free(cmd_path);
		wait_for_child(pid, &status, shell);
		return (shell->exit_status);
	}
	return (0);
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
	handle_execve_error(cmd_path);
}

char	*handle_absolute_path(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}
