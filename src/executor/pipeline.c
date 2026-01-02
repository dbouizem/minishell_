#include "../includes/minishell.h"

static int	**create_pipes(int num_pipes)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * num_pipes);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < num_pipes)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (cleanup_partial_pipes(pipes, i));
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			cleanup_partial_pipes(pipes, i + 1);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	setup_child_pipes(int **pipes, int cmd_index, int num_pipes)
{
	int	input_fd;
	int	output_fd;

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
			perror("minishell: dup2 input");
			exit(1);
		}
	}
	if (output_fd != STDOUT_FILENO && dup2(output_fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2 output");
		exit(1);
	}
}

void	cleanup_pipeline_resources(t_pipeline_data *data)
{
	int	i;

	if (data->pipes)
	{
		i = 0;
		while (i < data->num_pipes)
		{
			close(data->pipes[i][0]);
			close(data->pipes[i][1]);
			free(data->pipes[i]);
			i++;
		}
		free(data->pipes);
		data->pipes = NULL;
	}
	if (data->pids)
	{
		free(data->pids);
		data->pids = NULL;
	}
}

static void	init_pipeline_data(t_pipeline_data *data, t_cmd *cmd, t_shell *shell)
{
	data->cmd = cmd;
	data->shell = shell;
	data->num_commands = count_commands(cmd);
	data->num_pipes = data->num_commands - 1;
	data->pipes = NULL;
	data->pids = NULL;
	data->pipes = create_pipes(data->num_pipes);
}

int	execute_pipeline(t_cmd *cmd, t_shell *shell)
{
	t_pipeline_data	data;
	int				final_status;

	if (!cmd || !cmd->next)
		return (execute_command(cmd, shell));
	init_pipeline_data(&data, cmd, shell);
	if (!data.pipes)
		return (handle_pipe_error());
	data.pids = malloc(sizeof(pid_t) * data.num_commands);
	if (!data.pids)
	{
		cleanup_pipeline_resources(&data);
		return (handle_malloc_error());
	}
	fork_all_commands(&data);
	close_all_pipes(data.pipes, data.num_pipes);
	final_status = wait_all_children(data.pids, data.num_commands);
	cleanup_pipeline_resources(&data);
	return (final_status);
}
