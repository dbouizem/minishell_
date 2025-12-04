#include "../includes/minishell.h"

static int	count_commands(t_cmd *cmd)
{
	int		count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

static void	close_all_pipes(int **pipes, int num_pipes)
{
	int		i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

static void	free_pipes(int **pipes, int num_pipes)
{
	int		i;

	if (!pipes)
		return ;
	i = 0;
	while (i < num_pipes)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

static int	**create_pipes(int num_pipes)
{
	int		**pipes;
	int		i;

	pipes = malloc(sizeof(int *) * num_pipes);
	if (!pipes)
		return (NULL);

	i = 0;
	while (i < num_pipes)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			while (--i >= 0)
				free(pipes[i]);
			free(pipes);
			return (NULL);
		}
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			while (i >= 0)
			{
				free(pipes[i]);
				i--;
			}
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

static void	exec_child(t_cmd *cmd, t_shell *shell, int **pipes, int num_pipes, int cmd_index)
{
	int		input_fd;
	int		output_fd;

	if (cmd_index == 0)
		input_fd = STDIN_FILENO;
	else
		input_fd = pipes[cmd_index - 1][0];

	if (cmd_index == num_pipes)
		output_fd = STDOUT_FILENO;
	else
		output_fd = pipes[cmd_index][1];
	if (input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 input");
			exit(1);
		}
	}
	if (output_fd != STDOUT_FILENO)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 output");
			exit(1);
		}
	}
	close_all_pipes(pipes, num_pipes);
	execute_command_child(cmd, shell);
}


static int	wait_all_children(pid_t *pids, int num_commands)
{
	int		i;
	int		status;
	int		last_status;

	last_status = 0;
	i = 0;
	while (i < num_commands)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else
			last_status = 1;
		i++;
	}
	return (last_status);
}

int	execute_pipeline(t_cmd *cmd, t_shell *shell)
{
	int		num_commands;
	int		num_pipes;
	int		**pipes;
	pid_t	*pids;
	t_cmd	*current;
	int		i;
	int		final_status;

	if (!cmd || !cmd->next)
		return (execute_command(cmd, shell));

	num_commands = count_commands(cmd);
	num_pipes = num_commands - 1;

	pipes = create_pipes(num_pipes);
	if (!pipes)
	{
		perror("create_pipes");
		return (1);
	}
	pids = malloc(sizeof(pid_t) * num_commands);
	if (!pids)
	{
		close_all_pipes(pipes, num_pipes);
		free_pipes(pipes, num_pipes);
		return (1);
	}
	current = cmd;
	i = 0;
	while (i < num_commands)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			close_all_pipes(pipes, num_pipes);
			free_pipes(pipes, num_pipes);
			free(pids);
			return (1);
		}

		if (pids[i] == 0)
			exec_child(current, shell, pipes, num_pipes, i);
		current = current->next;
		i++;
	}
	close_all_pipes(pipes, num_pipes);
	final_status = wait_all_children(pids, num_commands);
	free_pipes(pipes, num_pipes);
	free(pids);
	return (final_status);
}
