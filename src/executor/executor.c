#include "../includes/minishell.h"

void	debug_command(t_cmd *cmd)
{
	int i = 0;

	printf("=== COMMAND DEBUG ===\n");
	while (cmd)
	{
		printf("Command %d:\n", i);
		if (cmd->args)
		{
			printf("  Args: ");
			for (int j = 0; cmd->args[j]; j++)
				printf("[%s] ", cmd->args[j]);
			printf("\n");
		}

		t_redir *redir = cmd->redirs;
		while (redir)
		{
			printf("  Redir: type=%d, file=%s\n", redir->type, redir->file);
			redir = redir->next;
		}

		cmd = cmd->next;
		i++;
	}
	printf("=====================\n");
}

int	execute(t_cmd *cmd, t_shell *shell)
{
	int		exit_status;

	if (!cmd)
		return (1);

	debug_command(cmd);
	printf("[EXECUTE] Starting execution\n");
	printf("[EXECUTE] Expanding variables\n");
	expand_commands(cmd, shell);

	printf("[EXECUTE] Removing quotes\n");
	remove_quotes_from_command(cmd);

	if (cmd->next)
	{
		printf("[EXECUTE] Pipeline detected\n");
		exit_status = execute_pipeline(cmd, shell);
	}
	else
	{
		printf("[EXECUTE] Single command\n");
		exit_status = execute_command(cmd, shell);
	}

	shell->exit_status = exit_status;
	printf("[EXECUTE] Finished with status %d\n", exit_status);
	return (exit_status);
}

int	execute_command(t_cmd *cmd, t_shell *shell)
{
	int		exit_status;
	int		saved_stdin = -1;
	int		saved_stdout = -1;

	if (!cmd)
		return (1);

	printf("[DEBUG execute_command] Starting execution\n");

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
	{
		perror("dup");
		return (1);
	}

	printf("[DEBUG] Setting up redirections\n");
	if (setup_redirections(cmd) != 0)
	{
		printf("[DEBUG] Redirection failed\n");
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}

	printf("[DEBUG] Executing command\n");
	if (cmd->args && cmd->args[0])
	{
		printf("[DEBUG] Command: %s\n", cmd->args[0]);
		if (is_builtin(cmd->args[0]))
		{
			printf("[DEBUG] Builtin detected\n");
			exit_status = execute_builtin(cmd, shell);
		}
		else
		{
			printf("[DEBUG] External command\n");
			exit_status = execute_external(cmd, shell);
		}
	}
	else
	{
		printf("[DEBUG] No command to execute\n");
		exit_status = 0;
	}
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		perror("dup2 stdin restore");
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		perror("dup2 stdout restore");
	close(saved_stdin);
	close(saved_stdout);

	printf("[DEBUG execute_command] Finished with status %d\n", exit_status);
	return (exit_status);
}
