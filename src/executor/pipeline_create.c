#include "../../includes/minishell.h"

static int	init_pipe_entry(int **pipes, int index)
{
	pipes[index] = malloc(sizeof(int) * 2);
	if (!pipes[index])
		return (0);
	pipes[index][0] = -1;
	pipes[index][1] = -1;
	if (pipe(pipes[index]) == -1)
		return (0);
	return (1);
}

static int	**cleanup_partial_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pipes[i])
		{
			if (pipes[i][0] >= 0)
				close(pipes[i][0]);
			if (pipes[i][1] >= 0)
				close(pipes[i][1]);
			free(pipes[i]);
		}
		i++;
	}
	free(pipes);
	return (NULL);
}

int	**create_pipes(int num_pipes)
{
	int	**pipes;
	int	i;
	int	err;

	pipes = malloc(sizeof(int *) * num_pipes);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < num_pipes)
	{
		if (!init_pipe_entry(pipes, i))
		{
			err = errno;
			cleanup_partial_pipes(pipes, i + 1);
			errno = err;
			return (NULL);
		}
		i++;
	}
	return (pipes);
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
