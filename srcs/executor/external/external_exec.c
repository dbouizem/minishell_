#include "../../../includes/minishell.h"

static char	*get_cmd_path(char *cmd, t_shell *shell, int *path_error)
{
	char	*path;

	*path_error = PATH_ERR_NONE;
	if (ft_strchr(cmd, '/'))
		return (handle_absolute_path(cmd));
	path = get_env_value("PATH", shell);
	return (search_in_paths(path, cmd, path_error));
}

static int	handle_missing_cmd(char *cmd, int path_error, t_shell *shell)
{
	if (path_error == PATH_ERR_ISDIR)
		print_error_is_directory(cmd, shell, 126);
	else if (path_error == PATH_ERR_PERM)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
		shell->exit_status = 126;
	}
	else
		handle_exec_error(cmd, shell);
	return (shell->exit_status);
}

static void	exec_child(char *cmd_path, t_cmd *cmd, t_shell *shell)
{
	ft_gnl_clear();
	setup_child_signals();
	env_list_to_array(shell);
	execve(cmd_path, cmd->args, shell->env);
	handle_execve_error(cmd_path, shell);
}

int	execute_external(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;
	int		path_error;
	char	*cmd_path;

	cmd_path = get_cmd_path(cmd->args[0], shell, &path_error);
	if (!cmd_path)
		return (handle_missing_cmd(cmd->args[0], path_error, shell));
	pid = fork_process();
	if (pid == 0)
		exec_child(cmd_path, cmd, shell);
	if (pid == -1)
	{
		free(cmd_path);
		shell->exit_status = 1;
		return (1);
	}
	free(cmd_path);
	wait_for_child(pid, &status, shell);
	return (shell->exit_status);
}

void	execute_external_no_fork(t_cmd *cmd, t_shell *shell)
{
	int		path_error;
	char	*cmd_path;

	if (!cmd || !cmd->args || !cmd->args[0])
		exit_child(1, shell);
	cmd_path = get_cmd_path(cmd->args[0], shell, &path_error);
	if (!cmd_path)
		exit_child(handle_missing_cmd(cmd->args[0], path_error, shell), shell);
	exec_child(cmd_path, cmd, shell);
}
