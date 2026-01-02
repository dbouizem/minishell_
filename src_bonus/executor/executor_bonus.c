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
	status = setup_redirections(cmd);
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

static int	should_execute_next(t_cmd *cmd, int last_exit_status)
{
	if (!cmd || !cmd->separator)
		return (0);
	if (cmd->separator == AND)
		return (last_exit_status == 0);
	if (cmd->separator == OR)
		return (last_exit_status != 0);
	if (cmd->separator == PIPE)
		return (1);
	return (0);
}

static t_cmd	*get_pipeline_end(t_cmd *start)
{
	t_cmd	*current;

	current = start;
	while (current && current->next && current->separator == PIPE)
		current = current->next;
	return (current);
}

static int	execute_sequence(t_cmd *cmd, t_shell *shell)
{
	int		exit_status;
	t_cmd	*current;
	t_cmd	*pipeline_end;

	current = cmd;
	exit_status = 0;
	while (current)
	{
		if (current->separator == PIPE && current->next)
		{
			pipeline_end = get_pipeline_end(current);
			exit_status = execute_pipeline(current, shell);
			shell->exit_status = exit_status;
			current = pipeline_end;
		}
		else
		{
			exit_status = execute_command(current, shell);
			shell->exit_status = exit_status;
		}
		if (!should_execute_next(current, exit_status))
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
