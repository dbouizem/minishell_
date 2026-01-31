/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:55:44 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/31 19:14:55 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	count_commands(t_cmd *cmd)
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

static void	init_pids(pid_t *pids, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pids[i] = -1;
		i++;
	}
}

static int	init_pipeline_data(t_pipeline_data *data, t_cmd *cmd,
		t_shell *shell)
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
	init_pids(data->pids, data->num_commands);
	return (0);
}

static int	prepare_pipeline(t_cmd *cmd, t_shell *shell)
{
	int	status;

	status = prepare_pipeline_heredocs(cmd, shell);
	if (status == 0)
		return (0);
	if (status == 130)
		shell->exit_status = 130;
	else
		shell->exit_status = 1;
	return (shell->exit_status);
}

int	execute_pipeline(t_cmd *cmd, t_shell *shell)
{
	t_pipeline_data	data;
	int				status;
	int				num_forked;

	if (!cmd || !cmd->next)
		return (execute_command(cmd, shell));
	status = prepare_pipeline(cmd, shell);
	if (status != 0)
		return (status);
	if (init_pipeline_data(&data, cmd, shell) != 0)
	{
		close_pipeline_heredocs(cmd);
		return (1);
	}
	num_forked = fork_all_commands(&data);
	close_all_pipes(data.pipes, data.num_pipes);
	close_pipeline_heredocs(cmd);
	if (num_forked > 0)
		status = wait_all_children(data.pids, num_forked, shell);
	else
		status = 1;
	if (num_forked < data.num_commands)
		status = 1;
	cleanup_pipeline_resources(&data);
	return (status);
}
