#include "../includes/minishell.h"

void	free_paths(char **paths)
{
	int i;

	i = 0;
	if (!paths || !*paths)
		return ;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*find_path(char *arg, t_shell *shell)
{
	char	**paths;
	char	*path_env;
	char	*full_path;
	char	*temp;
	int		i;

	if (ft_strchr(arg, '/'))
	{
		if (access(arg, X_OK) == 0)
			return (ft_strdup(arg));
		return (NULL);
	}
	path_env = get_env_value("PATH", shell);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, arg);
		free(temp);
		if (access(full_path, X_OK) == 0)
		{
			free_paths(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	if (paths)
		free_paths(paths);
	return (NULL);
}

int	execute_ext(t_cmd *cmds, t_shell *shell)
{
	char	*cmd_path;
	int		exit_status;
	pid_t	pid;

	cmd_path = find_path(cmds->args[0], shell);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmds->args[0], 2);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, cmds->args, shell->env);
		perror("minishell: execve");
		exit(126);
	}
	if (pid == -1)
	{
		perror("minishell: fork");
		free(cmd_path);
		return (1);
	}
	free(cmd_path);
	waitpid(pid, &exit_status, 0);
	if (exit_status > 1)
		exit_status = 1;
	return (exit_status);
}
