#include "../includes/minishell.h"

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

static int execute_sequence_bonus(t_cmd *cmd, t_shell *shell)
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
		if (!should_execute_next(exit_status, current->separator))
			skip_to_next_logical_operator(&current);
		current = current->next;
	}
	return (exit_status);
}
