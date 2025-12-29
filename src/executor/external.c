#include "../../includes/minishell.h"

#define PATH_ERR_NONE 0
#define PATH_ERR_PERM 1
#define PATH_ERR_ISDIR 2

static int	is_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		return (1);
	return (0);
}

static void	set_path_error(int is_dir, int *path_error)
{
	if (!path_error || *path_error != PATH_ERR_NONE)
		return ;
	if (is_dir)
		*path_error = PATH_ERR_ISDIR;
	else
		*path_error = PATH_ERR_PERM;
}

static char	*build_full_path(const char *path, size_t start, size_t len,
		char *cmd)
{
	char	*dir;
	char	*full_path;

	if (len == 0)
		dir = ft_strdup(".");
	else
		dir = ft_substr(path, start, len);
	if (!dir)
		return (NULL);
	full_path = ft_strjoin3(dir, "/", cmd);
	free(dir);
	return (full_path);
}

char	*search_in_paths(const char *path, char *cmd, int *path_error)
{
	size_t	i;
	size_t	start;
	char	*full_path;

	if (!path)
		return (NULL);
	i = 0;
	start = 0;
	while (1)
	{
		if (path[i] == ':' || path[i] == '\0')
		{
			full_path = build_full_path(path, start, i - start, cmd);
			if (!full_path)
				return (NULL);
		if (access(full_path, F_OK) == 0)
		{
			if (is_directory(full_path))
			{
				set_path_error(1, path_error);
				free(full_path);
			}
			else if (access(full_path, X_OK) == 0)
				return (full_path);
			else
			{
				set_path_error(0, path_error);
				free(full_path);
			}
		}
		else
			free(full_path);
		if (path[i] == '\0')
			break ;
		start = i + 1;
		}
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, t_shell *shell, int *path_error)
{
	char	*full_path;
	char	*path;

	if (ft_strchr(cmd, '/'))
		return (handle_absolute_path(cmd));
	path = get_env_value("PATH", shell);
	if (!path)
		return (NULL);
	full_path = search_in_paths(path, cmd, path_error);
	return (full_path);
}

static void	print_path_error(char *cmd, int path_error, t_shell *shell)
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
}

int	execute_external(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;
	int		path_error;

	path_error = PATH_ERR_NONE;
	cmd_path = find_command_path(cmd->args[0], shell, &path_error);
	if (!cmd_path)
	{
		if (path_error != PATH_ERR_NONE)
		{
			print_path_error(cmd->args[0], path_error, shell);
			return (shell->exit_status);
		}
		handle_exec_error(cmd->args[0], shell);
		return (shell->exit_status);
	}
	pid = fork_process();
	if (pid == 0)
	{
		setup_child_signals();
		env_list_to_array(shell);
		execve(cmd_path, cmd->args, shell->env);
		handle_execve_error(cmd_path);
	}
	else if (pid == -1)
	{
		free(cmd_path);
		shell->exit_status = 1;
		return (shell->exit_status);
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
	int		path_error;

	if (!cmd || !cmd->args || !cmd->args[0])
		exit(1);
	path_error = PATH_ERR_NONE;
	cmd_path = find_command_path(cmd->args[0], shell, &path_error);
	if (!cmd_path)
	{
		if (path_error != PATH_ERR_NONE)
		{
			print_path_error(cmd->args[0], path_error, shell);
			exit(shell->exit_status);
		}
		handle_exec_error(cmd->args[0], shell);
		exit(shell->exit_status);
	}
	env_list_to_array(shell);
	execve(cmd_path, cmd->args, shell->env);
	handle_execve_error(cmd_path);
}

char	*handle_absolute_path(char *cmd)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) == -1)
		return (NULL);
	if (S_ISDIR(path_stat.st_mode))
		return (NULL);
	if (access(cmd, X_OK) != 0)
		return (NULL);
	return (ft_strdup(cmd));
}
