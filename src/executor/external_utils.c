#include "../../includes/minishell.h"

void	free_string_array(char **array)
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

pid_t	fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	return (pid);
}

void	wait_for_child(pid_t pid, int *status, t_shell *shell)
{
	if (waitpid(pid, status, 0) == -1)
		perror("waitpid");
	if (WIFEXITED(*status))
		shell->exit_status = WEXITSTATUS(*status);
	else
		shell->exit_status = 1;
}

void	handle_execve_error(char *cmd_path)
{
	perror("execve");
	free(cmd_path);
	exit(127);
}

int	handle_pipe_error(void)
{
	perror("pipe");
	return (1);
}
