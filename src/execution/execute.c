#include "../../includes/minishell.h"

int	apply_single_redir(t_redir *redir);

int	apply_redirections(t_redir *redirs)
{
	t_redir	*current;

	current = redirs;
	while (current)
	{
		if (!apply_single_redir(current))
			return (0);
		current = current->next;
	}
	return (1);
}

static int	execute_simple_command(t_cmd *cmd, t_shell *shell)
{
	int		exit_status;

	if (!apply_redirections(cmd->redirs))
		return (1);
	if (is_builtin(cmd->args[0]))
		exit_status = execute_builtin(cmd, shell);
	else
		exit_status = execute_ext(cmd, shell);
	return (exit_status);
}

int	execute_commands(t_cmd *cmd, t_shell *shell)
{
	int	exit_status;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	/*Redir + oper*/
	exit_status = execute_simple_command(cmd, shell);
	//printf("%d\n", exit_status);
	shell->exit_status = exit_status;
	return (exit_status);
}
