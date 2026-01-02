#include "../includes/minishell.h"

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

static void	expand_all_wildcards(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		process_wildcards(current);
		current = current->next;
	}
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
	expand_all_wildcards(cmd);
	exit_status = execute_sequence(cmd, shell);
	shell->exit_status = exit_status;
	return (exit_status);
}