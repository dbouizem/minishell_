#include "../../includes/minishell.h"

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
		pipes[i][0] = -1;
		pipes[i][1] = -1;
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

	input_fd = STDIN_FILENO;
	if (cmd_index > 0)
		input_fd = pipes[cmd_index - 1][0];
	output_fd = STDOUT_FILENO;
	if (cmd_index < num_pipes)
		output_fd = pipes[cmd_index][1];
	if (input_fd != STDIN_FILENO && dup2(input_fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2 input");
		exit(1);
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

static int	init_pipeline_data(t_pipeline_data *data,
		t_cmd *cmd, t_shell *shell)
{
	data->cmd = cmd;
	data->shell = shell;
	data->num_commands = count_commands(cmd);
	data->num_pipes = data->num_commands - 1;
	data->pipes = create_pipes(data->num_pipes);
	if (!data->pipes)
		return (handle_pipe_error());
	data->pids = malloc(sizeof(pid_t) * data->num_commands);
	if (!data->pids)
	{
		cleanup_pipeline_resources(data);
		return (handle_malloc_error());
	}
	{
		int	i;

		i = 0;
		while (i < data->num_commands)
		{
			data->pids[i] = -1;
			i++;
		}
	}
	return (0);
}

int	execute_pipeline(t_cmd *cmd, t_shell *shell)
{
	t_pipeline_data	data;
	int				final_status;
	int				status;
	int				num_forked;

	if (!cmd || !cmd->next)
		return (execute_command(cmd, shell));
	status = init_pipeline_data(&data, cmd, shell);
	if (status != 0)
		return (status);
	num_forked = fork_all_commands(&data);
	close_all_pipes(data.pipes, data.num_pipes);
	if (num_forked > 0)
		final_status = wait_all_children(data.pids, num_forked, shell);
	else
		final_status = 1;
	if (num_forked < data.num_commands)
		final_status = 1;
	cleanup_pipeline_resources(&data);
	return (final_status);
}
