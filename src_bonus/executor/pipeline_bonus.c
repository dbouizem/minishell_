#include "../../includes/minishell.h"
#include "../../includes/wildcard.h"

static t_cmd	*get_pipeline_end(t_cmd *start)
{
	t_cmd	*current;

	current = start;
	while (current && current->next && current->separator == PIPE)
		current = current->next;
	return (current);
}

int	execute_sequence(t_cmd *cmd, t_shell *shell)
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