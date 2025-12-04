// srcs/debug/debug_executor.c - VERSION CORRIGÉE
#include "../includes/minishell.h"

/**
 * Affiche le type de redirection en string
 */
static const char	*redir_type_to_str(int type)
{
	static const char	*names[] = {
		"NONE", "INPUT", "TRUNC", "HEREDOC", "APPEND"
	};

	if (type >= 0 && type <= 4)
		return (names[type]);
	return ("UNKNOWN");
}

/**
 * Affiche une commande avec ses arguments et redirections
 */
void	print_command(t_cmd *cmd, int cmd_num)
{
	int		i;
	t_redir	*redir;

	printf("┌─────── COMMAND %d ───────┐\n", cmd_num);

	// Arguments
	if (cmd->args)
	{
		printf("│ Args: ");
		i = 0;
		while (cmd->args[i])
		{
			printf("[%s] ", cmd->args[i]);
			i++;
		}
		printf("\n");
	}
	else
	{
		printf("│ Args: (none)\n");
	}

	// Redirections
	redir = cmd->redirs;
	if (redir)
	{
		printf("│ Redirections:\n");
		while (redir)
		{
			printf("│   %-8s → %s\n",
				redir_type_to_str(redir->type),
				redir->file ? redir->file : "(null)");
			redir = redir->next;
		}
	}
	else
	{
		printf("│ Redirections: (none)\n");
	}

	printf("└──────────────────────────┘\n");
}

/**
 * Affiche tout le pipeline
 */
void	print_pipeline(t_cmd *cmd)
{
	int		cmd_num;
	t_cmd	*first_cmd;

	if (!cmd)
	{
		printf("\n=== NO COMMANDS ===\n");
		return;
	}

	// Garder une référence au premier pour le comptage
	first_cmd = cmd;

	printf("\n══════════ PIPELINE DEBUG ══════════\n");

	// Compter les commandes
	cmd_num = 0;
	while (cmd)
	{
		cmd_num++;
		cmd = cmd->next;
	}
	printf("Number of commands: %d\n\n", cmd_num);

	// Réafficher chaque commande
	cmd = first_cmd;
	cmd_num = 0;
	while (cmd)
	{
		print_command(cmd, cmd_num++);
		if (cmd->next)
			printf("                 ↓\n                 PIPE\n                 ↓\n");
		cmd = cmd->next;
	}
	printf("══════════════════════════════════════\n\n");
}

/**
 * Debug d'expansion : avant/après
 */
void	print_expansion_debug(t_cmd *cmd, const char *phase)
{
	int		i;
	t_cmd	*current;

	printf("\n─── %s ───\n", phase);
	current = cmd;
	while (current)
	{
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				printf("  arg[%d]: \"%s\"\n", i, current->args[i]);
				i++;
			}
		}
		current = current->next;
	}
	printf("──────────\n\n");
}

/**
 * Debug des file descriptors (utile pour pipelines)
 */
void	print_fd_debug(const char *context)
{
	printf("[FD DEBUG %s] stdin=%d, stdout=%d, stderr=%d\n",
		context, STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO);
}

/**
 * Debug d'exécution (avant/après chaque étape)
 */
void	print_execution_step(const char *step, t_cmd *cmd, t_shell *shell)
{
	(void)cmd;
	printf("\n═══════════════════════════════════════════\n");
	printf("STEP: %s\n", step);
	printf("Exit status: %d\n", shell->exit_status);
	printf("═══════════════════════════════════════════\n");
}

/**
 * Debug compact tout-en-un (style print_tokens)
 */
void	debug_executor(t_cmd *cmd, t_shell *shell, const char *phase)
{
	int		cmd_count;
	t_cmd	*current;
	int		i;

	(void)shell;

	printf("\n══════ EXECUTOR DEBUG [%s] ══════\n", phase);

	if (!cmd)
	{
		printf("No commands\n");
		printf("═══════════════════════════════\n\n");
		return;
	}

	// Compter et afficher les commandes
	current = cmd;
	cmd_count = 0;
	while (current)
	{
		cmd_count++;
		current = current->next;
	}

	printf("Total commands: %d\n", cmd_count);
	printf("─────────────────────────────────\n");

	// Afficher chaque commande
	current = cmd;
	cmd_count = 0;
	while (current)
	{
		printf("Cmd #%d:\n", cmd_count++);
		printf("  Args: ");
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				printf("\"%s\" ", current->args[i]);
				i++;
			}
		}
		printf("\n");

		// Redirections
		if (current->redirs)
		{
			t_redir *redir = current->redirs;
			printf("  Redirs: ");
			while (redir)
			{
				printf("%s->%s ",
					redir_type_to_str(redir->type),
					redir->file);
				redir = redir->next;
			}
			printf("\n");
		}

		if (current->next)
			printf("  └── PIPE ──┐\n");
		current = current->next;
	}

	printf("═══════════════════════════════\n\n");
}
