#include "../includes/minishell.h"

int	count_commands(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

int	**cleanup_partial_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			free(pipes[i]);
		}
		i++;
	}
	free(pipes);
	return (NULL);
}

void	fork_all_commands(t_pipeline_data *data)
{
	int		i;
	t_cmd	*current_cmd;

	i = 0;
	current_cmd = data->cmd;
	while (i < data->num_pipes + 1 && current_cmd)
	{
		data->pids[i] = fork();
		if (data->pids[i] == 0)
		{
			setup_child_pipes(data->pipes, i, data->num_pipes);
			cleanup_child_pipes(data->pipes, data->num_pipes, i);
			execute_command_child(current_cmd, data->shell);
			exit(1);
		}
		else if (data->pids[i] > 0)
			current_cmd = current_cmd->next;
		else
		{
			perror("minishell: fork");
			break ;
		}
		i++;
	}
}

void	close_all_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

int	wait_all_children(pid_t *pids, int num_commands)
{
	int	i;
	int	status;
	int	last_status;
	int	sig;

	last_status = 0;
	i = 0;
	while (i < num_commands)
	{
		waitpid(pids[i], &status, 0);
		if (i == num_commands - 1)
		{
			if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				if (sig == SIGINT)
					last_status = 130;
				else if (sig == SIGQUIT)
				{
					last_status = 131;
					write(STDERR_FILENO, "Quit (core dumped)\n", 19);
				}
				else
					last_status = 128 + sig;
			}
			else if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else
				last_status = 1;
		}
		i++;
	}
	return (last_status);
}
