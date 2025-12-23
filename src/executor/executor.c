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

static void skip_to_next_logical_operator(t_cmd **current)
{
	int current_sep;

	if (!*current || !(*current)->next)
		return;

	current_sep = (*current)->separator;
	while (*current && (*current)->next && (*current)->separator == current_sep)
			*current = (*current)->next;
}

static int should_execute_next(int exit_status, int separator)
{
	if (separator == AND)  // &&
		return (exit_status == 0);
	if (separator == OR)   // ||
		return (exit_status != 0);
	return (1);  // PIPE ou rien
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

static int execute_sequence(t_cmd *cmd, t_shell *shell)
{
	int		exit_status;
	t_cmd	*current;
	t_cmd	*pipe_start;

	current = cmd;
	exit_status = 0;
	while (current)
	{
		if (current->next && current->separator == PIPE)
		{
			pipe_start = current;
			while (current->next && current->separator == PIPE)
				current = current->next;
			exit_status = execute_pipeline(pipe_start, shell);
			shell->exit_status = exit_status;
		}
		else
		{
			exit_status = execute_command(current, shell);
			shell->exit_status = exit_status;
		}
		if (!current->next)
			break;
		//int statis = should_execute_next(exit_status, current->separator);
		//printf("should execute next = %d\n", statis);
		if (!should_execute_next(exit_status, current->separator))
		{
			skip_to_next_logical_operator(&current);
			//printf("current command %s et current sep %d\n", current->args[0],current->separator);
		}
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
	// Debug: afficher le statut de sortie final
	// fprintf(stderr, "Exit status: %d\n", exit_status);
	return (exit_status);
}
