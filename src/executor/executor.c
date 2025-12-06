#include "../includes/minishell.h"

int	execute(t_cmd *cmd, t_shell *shell)
{
	int	exit_status;

	if (!cmd)
	{
		shell->exit_status = 1;
		return (1);
	}
	expand_commands(cmd, shell);
	remove_quotes_from_command(cmd);
	if (cmd->next)
		exit_status = execute_pipeline(cmd, shell);
	else
		exit_status = execute_command(cmd, shell);
	shell->exit_status = exit_status;
	// Debug: afficher le statut de sortie final
	// fprintf(stderr, "Exit status: %d\n", exit_status);
	return (exit_status);
}

static int	handle_command_execution(t_cmd *cmd, t_shell *shell,
				int saved_in, int saved_out)
{
	int	exit_status;

	if (!cmd->args || !cmd->args[0])
		exit_status = 0;
	else if (is_builtin(cmd->args[0]))
		exit_status = execute_builtin(cmd, shell);
	else
		exit_status = execute_external(cmd, shell);
	shell->exit_status = exit_status;
	restore_redirections(saved_in, saved_out);
	return (exit_status);
}

int	execute_command(t_cmd *cmd, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;

	if (save_redirections(&saved_stdin, &saved_stdout) != 0)
	{
		shell->exit_status = 1;
		return (1);
	}
	if (setup_redirections(cmd) != 0)
	{
		shell->exit_status = 1;
		restore_redirections(saved_stdin, saved_stdout);
		return (1);
	}
	return (handle_command_execution(cmd, shell, saved_stdin, saved_stdout));
}

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

void	execute_command_child(t_cmd *cmd, t_shell *shell)
{
	int		exit_status;
	t_cmd	cmd_copy;

	if (!cmd)
		exit(1);

	cmd_copy.args = cmd->args;
	cmd_copy.redirs = cmd->redirs;
	cmd_copy.next = NULL;

	remove_quotes_from_command(&cmd_copy);

	if (setup_redirections(&cmd_copy) != 0)
		exit(1);

	if (cmd_copy.args && cmd_copy.args[0])
	{
		if (is_builtin(cmd_copy.args[0]))
		{
			exit_status = execute_builtin(&cmd_copy, shell);
			exit(exit_status);
		}
		else
		{
			execute_external_no_fork(&cmd_copy, shell);
			exit(127);
		}
	}
	exit(0);
}
