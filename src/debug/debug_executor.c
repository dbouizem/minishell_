#include "../includes/minishell.h"

	// "NONE",          // 0
	// "REDIR_IN",      // 1  (était "INPUT")
	// "REDIR_OUT",     // 2  (était "TRUNC")
	// "REDIR_APPEND",  // 3  (était "HEREDOC")
	// "REDIR_HEREDOC"  // 4  (était "APPEND")

/**
 * Affiche le type de redirection en string
 */
static const char	*redir_type_to_str(int type)
{
const char	*names[] =
{
	"NONE", "REDIR_IN",	"REDIR_OUT", "REDIR_APPEND", "REDIR_HEREDOC"
};

	if (type >= 0 && type <= 4)
		return (names[type]);
	return ("UNKNOWN");
}

/**
 * Affiche une commande simple et propre
 */
void	print_command(t_cmd *cmd, int cmd_num)
{
	int		i;
	t_redir	*redir;

	printf("\n" COLOR_BOLD "=== COMMAND #%d ===" COLOR_RESET "\n", cmd_num);

	// Arguments
	printf(COLOR_BOLD "Args: " COLOR_RESET);
	if (cmd->args && cmd->args[0])
	{
		i = 0;
		while (cmd->args[i])
		{
			printf(COLOR_GREEN "%s" COLOR_RESET " ", cmd->args[i]);
			i++;
		}
		printf("\n");
	}
	else
		printf(COLOR_YELLOW "(none)\n" COLOR_RESET);

	// Redirections
	printf(COLOR_BOLD "Redirections: " COLOR_RESET);
	redir = cmd->redirs;
	if (redir)
	{
		printf("\n");
		while (redir)
		{
			if (redir->type == 1 || redir->type == 3)
				printf("  " COLOR_YELLOW "%s" COLOR_RESET, redir_type_to_str(redir->type));
			else if (redir->type == 2 || redir->type == 4)
				printf("  " COLOR_MAGENTA "%s" COLOR_RESET, redir_type_to_str(redir->type));
			else
				printf("  %s", redir_type_to_str(redir->type));

			printf(" -> %s\n", redir->file ? redir->file : COLOR_RED "(null)" COLOR_RESET);
			redir = redir->next;
		}
	}
	else
		printf(COLOR_YELLOW "(none)\n" COLOR_RESET);
}

/**
 * Affiche le pipeline complet
 */
void	print_pipeline(t_cmd *cmd)
{
	int		cmd_num;
	t_cmd	*current;
	int		total;

	if (!cmd)
	{
		printf(COLOR_RED "\n=== NO COMMANDS ===\n" COLOR_RESET);
		return;
	}

	// Compter les commandes
	total = 0;
	current = cmd;
	while (current)
	{
		total++;
		current = current->next;
	}

	printf("\n" COLOR_BOLD "========== PIPELINE DEBUG ==========\n" COLOR_RESET);
	printf(COLOR_BOLD "Total commands: " COLOR_CYAN "%d\n" COLOR_RESET, total);

	// Afficher chaque commande
	current = cmd;
	cmd_num = 0;
	while (current)
	{
		print_command(current, cmd_num);

		if (current->next)
			printf(COLOR_BLUE "\n        |  PIPE\n        v\n" COLOR_RESET);

		current = current->next;
		cmd_num++;
	}

	printf(COLOR_BOLD "\n====================================\n" COLOR_RESET);
}

/**
 * Debug expansion simple
 */
void	print_expansion_debug(t_cmd *cmd, const char *phase)
{
	int		i;
	t_cmd	*current;
	int		cmd_num;

	printf("\n" COLOR_MAGENTA "--- EXPANSION: %s ---\n" COLOR_RESET, phase);

	current = cmd;
	cmd_num = 0;
	while (current)
	{
		printf(COLOR_BOLD "Cmd #%d: " COLOR_RESET, cmd_num++);
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				printf(COLOR_GREEN "%s" COLOR_RESET " ", current->args[i]);
				i++;
			}
		}
		printf("\n");
		current = current->next;
	}
	printf("\n");
}

/**
 * Debug file descriptors
 */
void	print_fd_debug(const char *context)
{
	printf(COLOR_CYAN "\n[FD DEBUG: %s]\n" COLOR_RESET, context);
	printf("  stdin  = " COLOR_YELLOW "%d\n" COLOR_RESET, STDIN_FILENO);
	printf("  stdout = " COLOR_GREEN "%d\n" COLOR_RESET, STDOUT_FILENO);
	printf("  stderr = " COLOR_RED "%d\n" COLOR_RESET, STDERR_FILENO);
}

/**
 * Debug étape d'exécution
 */
void	print_execution_step(const char *step, t_cmd *cmd, t_shell *shell)
{
	(void)cmd;

	printf("\n" COLOR_BOLD "========== EXECUTION STEP ==========\n" COLOR_RESET);
	printf(COLOR_BOLD "Step: " COLOR_RESET COLOR_CYAN "%s\n" COLOR_RESET, step);

	if (shell->exit_status == 0)
		printf(COLOR_BOLD "Exit: " COLOR_GREEN "%d\n" COLOR_RESET, shell->exit_status);
	else
		printf(COLOR_BOLD "Exit: " COLOR_RED "%d\n" COLOR_RESET, shell->exit_status);

	printf(COLOR_BOLD "====================================\n" COLOR_RESET);
}

/**
 * Debug executor - Version simple et compacte
 */
void	debug_executor(t_cmd *cmd, t_shell *shell, const char *phase)
{
	int		cmd_count;
	t_cmd	*current;
	int		i;
	t_redir	*redir;

	(void)shell;

	printf("\n" COLOR_BOLD ">>> EXECUTOR DEBUG - %s <<<\n" COLOR_RESET, phase);

	if (!cmd)
	{
		printf(COLOR_RED "No commands\n" COLOR_RESET);
		return;
	}

	// Compter
	current = cmd;
	cmd_count = 0;
	while (current)
	{
		cmd_count++;
		current = current->next;
	}

	printf(COLOR_BOLD "Total: " COLOR_CYAN "%d command(s)\n" COLOR_RESET, cmd_count);
	printf("--------------------------------\n");

	// Afficher chaque commande
	current = cmd;
	cmd_count = 0;
	while (current)
	{
		printf("\n" COLOR_BOLD "[Cmd #%d]\n" COLOR_RESET, cmd_count++);

		// Args
		printf("  Args: ");
		if (current->args && current->args[0])
		{
			i = 0;
			while (current->args[i])
			{
				printf(COLOR_GREEN "%s" COLOR_RESET " ", current->args[i]);
				i++;
			}
			printf("\n");
		}
		else
			printf(COLOR_YELLOW "(none)\n" COLOR_RESET);

		// Redirections
		printf("  Redir: ");
		if (current->redirs)
		{
			redir = current->redirs;
			while (redir)
			{
				if (redir->type == 1 || redir->type == 3)
					printf(COLOR_YELLOW "%s" COLOR_RESET, redir_type_to_str(redir->type));
				else if (redir->type == 2 || redir->type == 4)
					printf(COLOR_MAGENTA "%s" COLOR_RESET, redir_type_to_str(redir->type));
				else
					printf("%s", redir_type_to_str(redir->type));

				printf("->%s ", redir->file ? redir->file : COLOR_RED "(null)" COLOR_RESET);
				redir = redir->next;
			}
			printf("\n");
		}
		else
			printf(COLOR_YELLOW "(none)\n" COLOR_RESET);

		if (current->next)
			printf(COLOR_BLUE "  [PIPE]\n" COLOR_RESET);

		current = current->next;
	}

	printf("\n" COLOR_GREEN ">>> Done <<<\n" COLOR_RESET);
}
