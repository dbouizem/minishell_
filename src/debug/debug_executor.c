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

	fprintf(stderr, "\n" COLOR_BOLD "=== COMMAND #%d ===" COLOR_RESET "\n", cmd_num);

	// Arguments
	fprintf(stderr, COLOR_BOLD "Args: " COLOR_RESET);
	if (cmd->args && cmd->args[0])
	{
		i = 0;
		while (cmd->args[i])
		{
			fprintf(stderr, COLOR_GREEN "%s" COLOR_RESET " ", cmd->args[i]);
			i++;
		}
		fprintf(stderr, "\n");
	}
	else
		fprintf(stderr, COLOR_YELLOW "(none)\n" COLOR_RESET);

	// Redirections
	fprintf(stderr, COLOR_BOLD "Redirections: " COLOR_RESET);
	redir = cmd->redirs;
	if (redir)
	{
		fprintf(stderr, "\n");
		while (redir)
		{
			if (redir->type == 1 || redir->type == 3)
				fprintf(stderr, "  " COLOR_YELLOW "%s" COLOR_RESET, redir_type_to_str(redir->type));
			else if (redir->type == 2 || redir->type == 4)
				fprintf(stderr, "  " COLOR_MAGENTA "%s" COLOR_RESET, redir_type_to_str(redir->type));
			else
				fprintf(stderr, "  %s", redir_type_to_str(redir->type));

			fprintf(stderr, " -> %s\n", redir->file ? redir->file : COLOR_RED "(null)" COLOR_RESET);
			redir = redir->next;
		}
	}
	else
		fprintf(stderr, COLOR_YELLOW "(none)\n" COLOR_RESET);
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
		fprintf(stderr, COLOR_RED "\n=== NO COMMANDS ===\n" COLOR_RESET);
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

	fprintf(stderr, "\n" COLOR_BOLD "========== PIPELINE DEBUG ==========\n" COLOR_RESET);
	fprintf(stderr, COLOR_BOLD "Total commands: " COLOR_CYAN "%d\n" COLOR_RESET, total);

	// Afficher chaque commande
	current = cmd;
	cmd_num = 0;
	while (current)
	{
		print_command(current, cmd_num);

		if (current->next)
			fprintf(stderr, COLOR_BLUE "\n        |  PIPE\n        v\n" COLOR_RESET);

		current = current->next;
		cmd_num++;
	}

	fprintf(stderr, COLOR_BOLD "\n====================================\n" COLOR_RESET);
}

/**
 * Debug expansion simple
 */
void	print_expansion_debug(t_cmd *cmd, const char *phase)
{
	int		i;
	t_cmd	*current;
	int		cmd_num;

	fprintf(stderr, "\n" COLOR_MAGENTA "--- EXPANSION: %s ---\n" COLOR_RESET, phase);

	current = cmd;
	cmd_num = 0;
	while (current)
	{
		fprintf(stderr, COLOR_BOLD "Cmd #%d: " COLOR_RESET, cmd_num++);
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				fprintf(stderr, COLOR_GREEN "%s" COLOR_RESET " ", current->args[i]);
				i++;
			}
		}
		fprintf(stderr, "\n");
		current = current->next;
	}
	fprintf(stderr, "\n");
}

/**
 * Debug file descriptors
 */
void	print_fd_debug(const char *context)
{
	fprintf(stderr, COLOR_CYAN "\n[FD DEBUG: %s]\n" COLOR_RESET, context);
	fprintf(stderr, "  stdin  = " COLOR_YELLOW "%d\n" COLOR_RESET, STDIN_FILENO);
	fprintf(stderr, "  stdout = " COLOR_GREEN "%d\n" COLOR_RESET, STDOUT_FILENO);
	fprintf(stderr, "  stderr = " COLOR_RED "%d\n" COLOR_RESET, STDERR_FILENO);
}

/**
 * Debug étape d'exécution
 */
void	print_execution_step(const char *step, t_cmd *cmd, t_shell *shell)
{
	(void)cmd;

	fprintf(stderr, "\n" COLOR_BOLD "========== EXECUTION STEP ==========\n" COLOR_RESET);
	fprintf(stderr, COLOR_BOLD "Step: " COLOR_RESET COLOR_CYAN "%s\n" COLOR_RESET, step);

	if (shell->exit_status == 0)
		fprintf(stderr, COLOR_BOLD "Exit: " COLOR_GREEN "%d\n" COLOR_RESET, shell->exit_status);
	else
		fprintf(stderr, COLOR_BOLD "Exit: " COLOR_RED "%d\n" COLOR_RESET, shell->exit_status);

	fprintf(stderr, COLOR_BOLD "====================================\n" COLOR_RESET);
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

	fprintf(stderr, "\n" COLOR_BOLD ">>> EXECUTOR DEBUG - %s <<<\n" COLOR_RESET, phase);

	if (!cmd)
	{
		fprintf(stderr, COLOR_RED "No commands\n" COLOR_RESET);
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

	fprintf(stderr, COLOR_BOLD "Total: " COLOR_CYAN "%d command(s)\n" COLOR_RESET, cmd_count);
	fprintf(stderr, "--------------------------------\n");

	// Afficher chaque commande
	current = cmd;
	cmd_count = 0;
	while (current)
	{
		fprintf(stderr, "\n" COLOR_BOLD "[Cmd #%d]\n" COLOR_RESET, cmd_count++);

		// Args
		fprintf(stderr, "  Args: ");
		if (current->args && current->args[0])
		{
			i = 0;
			while (current->args[i])
			{
				fprintf(stderr, COLOR_GREEN "%s" COLOR_RESET " ", current->args[i]);
				i++;
			}
			fprintf(stderr, "\n");
		}
		else
			fprintf(stderr, COLOR_YELLOW "(none)\n" COLOR_RESET);

		// Redirections
		fprintf(stderr, "  Redir: ");
		if (current->redirs)
		{
			redir = current->redirs;
			while (redir)
			{
				if (redir->type == 1 || redir->type == 3)
					fprintf(stderr, COLOR_YELLOW "%s" COLOR_RESET, redir_type_to_str(redir->type));
				else if (redir->type == 2 || redir->type == 4)
					fprintf(stderr, COLOR_MAGENTA "%s" COLOR_RESET, redir_type_to_str(redir->type));
				else
					fprintf(stderr, "%s", redir_type_to_str(redir->type));

				fprintf(stderr, "->%s ", redir->file ? redir->file : COLOR_RED "(null)" COLOR_RESET);
				redir = redir->next;
			}
			fprintf(stderr, "\n");
		}
		else
			fprintf(stderr, COLOR_YELLOW "(none)\n" COLOR_RESET);

		if (current->next)
			fprintf(stderr, COLOR_BLUE "  [PIPE]\n" COLOR_RESET);

		current = current->next;
	}

	fprintf(stderr, "\n" COLOR_GREEN ">>> Done <<<\n" COLOR_RESET);
}
