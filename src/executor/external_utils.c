#include "../includes/minishell.h"

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
	int	sig;

	if (waitpid(pid, status, 0) == -1)
	{
		perror("waitpid");
		shell->exit_status = 1;
		return ;
	}
	if (WIFSIGNALED(*status))
	{
		sig = WTERMSIG(*status);
		if (sig == SIGINT)
			shell->exit_status = 130;
		else if (sig == SIGQUIT)
		{
			shell->exit_status = 131;
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		}
		else
			shell->exit_status = 128 + sig;
	}
	else if (WIFEXITED(*status))
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
