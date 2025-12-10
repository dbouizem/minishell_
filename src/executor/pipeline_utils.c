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
		free(pipes[i]);
		i++;
	}
	free(pipes);
	return (NULL);
}

void	fork_all_commands(t_pipeline_data *data)
{
	int		i;
	t_cmd	*current_cmd;

	// debug_fork_header(data->num_commands);

	i = 0;
	current_cmd = data->cmd;

	while (i < data->num_pipes + 1 && current_cmd)
	{
		// debug_fork_command(i, current_cmd);

		data->pids[i] = fork();
		if (data->pids[i] == 0)
		{
			//setup_child_signals();
			setup_child_pipes(data->pipes, i, data->num_pipes);
			cleanup_child_pipes(data->pipes, data->num_pipes, i);
			execute_command_child(current_cmd, data->shell);

			exit(1);
		}
		else if (data->pids[i] > 0)
		{
			// debug_fork_parent(i, data->pids[i]);
			current_cmd = current_cmd->next;
		}
		else
		{
			perror("minishell: fork");
			break ;
		}
		i++;
	}
	// debug_fork_footer();
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
