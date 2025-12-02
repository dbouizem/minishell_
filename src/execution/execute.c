#include "../../includes/minishell.h"

static int	execute_simple_command(t_cmd *cmd, t_shell *shell)
{
	int		exit_status;

	if (is_builtin(cmd->args[0]))
		exit_status = execute_builtin(cmd, shell);
	else
	//path cmd
		return (0);
	return (exit_status);
}

int	execute_commands(t_cmd *cmd, t_shell *shell)
{
	int	exit_status;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	/*Redir + oper*/
	exit_status = execute_simple_command(cmd, shell);
	shell->exit_status = exit_status;
	return (exit_status);
}
