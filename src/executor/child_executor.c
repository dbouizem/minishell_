#include "../includes/minishell.h"

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

static void	cleanup_and_exit(t_shell *shell, int status)
{
	cleanup_shell(shell);
	exit(status);
}

void	execute_command_child(t_cmd *cmd, t_shell *shell)
{
	int		exit_status;
	t_cmd	cmd_copy;

	setup_child_signals();
	if (!cmd)
		cleanup_and_exit(shell, 1);
	cmd_copy.args = cmd->args;
	cmd_copy.redirs = cmd->redirs;
	cmd_copy.next = NULL;
	//cmd_copy.separator = 0;
	if (setup_redirections(&cmd_copy) != 0)
		cleanup_and_exit(shell, 1);
	if (cmd_copy.args && cmd_copy.args[0])
	{
		if (is_builtin(cmd_copy.args[0]))
		{
			exit_status = execute_builtin(&cmd_copy, shell);
			cleanup_and_exit(shell, exit_status);
		}
		else
		{
			execute_external_no_fork(&cmd_copy, shell);
			cleanup_and_exit(shell, 127);
		}
	}
	cleanup_and_exit(shell, 0);
}
