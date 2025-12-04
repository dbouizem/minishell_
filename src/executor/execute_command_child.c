#include "../includes/minishell.h"

void	execute_command_child(t_cmd *cmd, t_shell *shell)
{
	int	exit_status;

	if (!cmd)
		exit(1);
	remove_quotes_from_command(cmd);
	if (setup_redirections(cmd) != 0)
		exit(1);
	if (cmd->args && cmd->args[0])
	{
		if (is_builtin(cmd->args[0]))
		{
			exit_status = execute_builtin(cmd, shell);
			exit(exit_status);
		}
		else
		{
			execute_external_no_fork(cmd, shell);
			exit(127);
		}
	}
	exit(0);
}
