#include "../includes/minishell.h"

static void	exec_in_pipeline(t_cmd *cmd, t_shell *shell, int input_fd, int output_fd)
{
	if (input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 input");
			exit(1);
		}
		close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 output");
			exit(1);
		}
		close(output_fd);
	}
	if (setup_redirections(cmd) != 0)
		exit(1);
	if (cmd->args && cmd->args[0])
	{
		if (is_builtin(cmd->args[0]))
		{
			int exit_status = execute_builtin(cmd, shell);
			exit(exit_status);
		}
		else
		{
			execute_external_no_fork(cmd, shell);
		}
	}
	exit(0);
}

int	execute_pipeline(t_cmd *cmd, t_shell *shell)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status1, status2;
	int		saved_stdin = -1;
	int		saved_stdout = -1;

	if (!cmd || !cmd->next)
		return (execute_command(cmd, shell));
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
	{
		perror("dup");
		return (1);
	}
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}

	if (pid1 == 0)
	{
		close(saved_stdin);
		close(saved_stdout);
		close(pipe_fd[0]);
		exec_in_pipeline(cmd, shell, STDIN_FILENO, pipe_fd[1]);
	}
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		waitpid(pid1, NULL, 0);
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}

	if (pid2 == 0)
	{
		close(saved_stdin);
		close(saved_stdout);
		close(pipe_fd[1]);
		exec_in_pipeline(cmd->next, shell, pipe_fd[0], STDOUT_FILENO);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		perror("dup2 stdin restore");
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		perror("dup2 stdout restore");
	close(saved_stdin);
	close(saved_stdout);
	if (WIFEXITED(status2))
		return (WEXITSTATUS(status2));
	return (1);
}
