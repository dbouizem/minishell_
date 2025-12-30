#include "../../includes/minishell.h"

static void	setup_child_pipes(int **pipes, int cmd_index, int num_pipes)
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

static void	exec_child_command(t_pipeline_data *data, t_cmd *cmd, int index)
{
	setup_child_signals();
	setup_child_pipes(data->pipes, index, data->num_pipes);
	cleanup_child_pipes(data->pipes, data->num_pipes, index);
	execute_command_child(cmd, data->shell);
	exit(1);
}

static int	fork_command(t_pipeline_data *data, t_cmd *cmd, int index)
{
	pid_t	pid;

	pid = fork();
	data->pids[index] = pid;
	if (pid == 0)
		exec_child_command(data, cmd, index);
	if (pid < 0)
	{
		perror("minishell: fork");
		return (-1);
	}
	return (0);
}

int	fork_all_commands(t_pipeline_data *data)
{
	int		i;
	t_cmd	*current_cmd;

	i = 0;
	current_cmd = data->cmd;
	while (i < data->num_pipes + 1 && current_cmd)
	{
		if (fork_command(data, current_cmd, i) == -1)
			break ;
		current_cmd = current_cmd->next;
		i++;
	}
	return (i);
}
