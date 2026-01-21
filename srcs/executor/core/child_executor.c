#include "../../../includes/minishell.h"

void	cleanup_child_pipes(int **pipes, int num_pipes, int cmd_index)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (i != cmd_index - 1)
			close(pipes[i][0]);
		if (i != cmd_index)
			close(pipes[i][1]);
		i++;
	}
}

static void	execute_child_command(t_cmd *cmd, t_shell *shell)
{
	int	exit_status;

	if (cmd->args && cmd->args[0])
	{
		if (is_builtin(cmd->args[0]))
		{
			exit_status = execute_builtin(cmd, shell);
			exit_child(exit_status, shell);
		}
		execute_external_no_fork(cmd, shell);
		exit_child(127, shell);
	}
	exit_child(0, shell);
}

void	execute_command_child(t_cmd *cmd, t_shell *shell)
{
	t_cmd	cmd_copy;
	int		status;

	if (!cmd)
		exit_child(1, shell);
	cmd_copy.args = cmd->args;
	cmd_copy.redirs = cmd->redirs;
	cmd_copy.next = NULL;
	status = setup_redirections(&cmd_copy, shell);
	if (status != 0)
		exit_child(status, shell);
	execute_child_command(&cmd_copy, shell);
}
