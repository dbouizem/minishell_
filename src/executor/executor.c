#include "../../includes/minishell.h"

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

static int	execute_current(t_cmd **current, t_shell *shell)
{
	int		exit_status;
	t_cmd	*pipe_start;

	if ((*current)->next && (*current)->separator == PIPE)
	{
		pipe_start = *current;
		while ((*current)->next && (*current)->separator == PIPE)
			*current = (*current)->next;
		exit_status = execute_pipeline(pipe_start, shell);
	}
	else
		exit_status = execute_command(*current, shell);
	shell->exit_status = exit_status;
	return (exit_status);
}

int	execute_command(t_cmd *cmd, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;

	if (save_redirections(&saved_stdin, &saved_stdout) != 0)
	{
		shell->exit_status = 1;
		return (1);
	}
	status = setup_redirections(cmd, shell);
	if (status == 130)
	{
		shell->exit_status = 130;
		restore_redirections(saved_stdin, saved_stdout);
		return (130);
	}
	if (status != 0)
	{
		shell->exit_status = 1;
		restore_redirections(saved_stdin, saved_stdout);
		return (1);
	}
	return (handle_command_execution(cmd, shell, saved_stdin, saved_stdout));
}

static int	execute_sequence(t_cmd *cmd, t_shell *shell)
{
	int		exit_status;
	t_cmd	*current;

	current = cmd;
	exit_status = 0;
	while (current)
	{
		exit_status = execute_current(&current, shell);
		if (!current->next)
			break ;
		current = current->next;
	}
	return (exit_status);
}

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
	exit_status = execute_sequence(cmd, shell);
	shell->exit_status = exit_status;
	return (exit_status);
}
