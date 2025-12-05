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

	printf(COLOR_BOLD COLOR_CYAN "┌───────" BG_BLUE COLOR_WHITE
		" COMMAND %d " COLOR_RESET COLOR_BOLD COLOR_CYAN "───────┐" COLOR_RESET "\n", cmd_num);

	// Arguments
	if (cmd->args)
	{
		printf(COLOR_CYAN "│" COLOR_RESET COLOR_BOLD " Args: " COLOR_RESET);
		i = 0;
		while (cmd->args[i])
		{
			printf(COLOR_GREEN "[%s] " COLOR_RESET, cmd->args[i]);
			i++;
		}
		printf("\n");
	}
	else
	{
		printf(COLOR_CYAN "│" COLOR_RESET COLOR_BOLD " Args: " COLOR_RESET
			COLOR_YELLOW "(none)" COLOR_RESET "\n");
	}

	// Redirections
	redir = cmd->redirs;
	if (redir)
	{
		printf(COLOR_CYAN "│" COLOR_RESET COLOR_BOLD " Redirections:" COLOR_RESET "\n");
		while (redir)
		{
			const char *type_color = COLOR_WHITE;
			if (redir->type == 1 || redir->type == 3) // INPUT ou HEREDOC
				type_color = COLOR_YELLOW;
			else if (redir->type == 2 || redir->type == 4) // TRUNC ou APPEND
				type_color = COLOR_MAGENTA;

			printf(COLOR_CYAN "│" COLOR_RESET "   %s%-8s" COLOR_RESET
				" → " COLOR_CYAN "%s" COLOR_RESET "\n",
				type_color,
				redir_type_to_str(redir->type),
				redir->file ? redir->file : COLOR_YELLOW "(null)" COLOR_RESET);
			redir = redir->next;
		}
	}
	else
	{
		printf(COLOR_CYAN "│" COLOR_RESET COLOR_BOLD " Redirections: " COLOR_RESET
			COLOR_YELLOW "(none)" COLOR_RESET "\n");
	}

	printf(COLOR_BOLD COLOR_CYAN "└──────────────────────────┘" COLOR_RESET "\n");
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
		printf(COLOR_RED "\n=== NO COMMANDS ===" COLOR_RESET "\n");
		return;
	}

	// Garder une référence au premier pour le comptage
	first_cmd = cmd;

	printf(COLOR_BOLD BG_BLUE COLOR_WHITE "\n══════════ PIPELINE DEBUG ══════════"
		COLOR_RESET "\n");

	// Compter les commandes
	cmd_num = 0;
	while (cmd)
	{
		cmd_num++;
		cmd = cmd->next;
	}
	printf(COLOR_BOLD "Number of commands: " COLOR_CYAN "%d" COLOR_RESET "\n\n", cmd_num);

	// Réafficher chaque commande
	cmd = first_cmd;
	cmd_num = 0;
	while (cmd)
	{
		print_command(cmd, cmd_num++);
		if (cmd->next)
			printf(COLOR_BLUE "                 ↓\n                 PIPE\n                 ↓\n" COLOR_RESET);
		cmd = cmd->next;
	}
	printf(COLOR_BOLD BG_BLUE COLOR_WHITE "══════════════════════════════════════"
		COLOR_RESET "\n\n");
}

/**
 * Debug d'expansion : avant/après
 */
void	print_expansion_debug(t_cmd *cmd, const char *phase)
{
	int		i;
	t_cmd	*current;

	printf(COLOR_BOLD COLOR_MAGENTA "\n─── %s ───" COLOR_RESET "\n", phase);
	current = cmd;
	while (current)
	{
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				printf("  " COLOR_BOLD "arg[%d]:" COLOR_RESET " \"" COLOR_GREEN "%s"
					COLOR_RESET "\"\n", i, current->args[i]);
				i++;
			}
		}
		current = current->next;
	}
	printf(COLOR_BOLD COLOR_MAGENTA "──────────" COLOR_RESET "\n\n");
}

/**
 * Debug des file descriptors (utile pour pipelines)
 */
void	print_fd_debug(const char *context)
{
	printf(COLOR_BOLD BG_CYAN COLOR_WHITE "[FD DEBUG %s]" COLOR_RESET
		" stdin=" COLOR_YELLOW "%d" COLOR_RESET
		", stdout=" COLOR_GREEN "%d" COLOR_RESET
		", stderr=" COLOR_RED "%d" COLOR_RESET "\n",
		context, STDIN_FILENO, STDOUT_FILENO, STDOUT_FILENO);
}

/**
 * Debug d'exécution (avant/après chaque étape)
 */
void	print_execution_step(const char *step, t_cmd *cmd, t_shell *shell)
{
	(void)cmd;

	const char *status_color = COLOR_GREEN;
	if (shell->exit_status != 0)
		status_color = COLOR_RED;

	printf(COLOR_BOLD BG_BLUE COLOR_WHITE "\n═══════════════════════════════════════════"
		COLOR_RESET "\n");
	printf(COLOR_BOLD "STEP: " COLOR_CYAN "%s" COLOR_RESET "\n", step);
	printf(COLOR_BOLD "Exit status: " COLOR_RESET "%s%d" COLOR_RESET "\n",
		status_color, shell->exit_status);
	printf(COLOR_BOLD BG_BLUE COLOR_WHITE "═══════════════════════════════════════════"
		COLOR_RESET "\n");
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

	printf(COLOR_BOLD BG_BLUE COLOR_WHITE "\n══════ EXECUTOR DEBUG [%s] ══════"
		COLOR_RESET "\n", phase);

	if (!cmd)
	{
		printf(COLOR_RED "No commands" COLOR_RESET "\n");
		printf(COLOR_BOLD BG_BLUE COLOR_WHITE "═══════════════════════════════"
			COLOR_RESET "\n\n");
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

	printf(COLOR_BOLD "Total commands: " COLOR_CYAN "%d" COLOR_RESET "\n", cmd_count);
	printf(COLOR_BOLD "─────────────────────────────────" COLOR_RESET "\n");

	// Afficher chaque commande
	current = cmd;
	cmd_count = 0;
	while (current)
	{
		printf(COLOR_BOLD "Cmd #%d:" COLOR_RESET "\n", cmd_count++);
		printf("  " COLOR_BOLD "Args:" COLOR_RESET " ");
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				printf("\"" COLOR_GREEN "%s" COLOR_RESET "\" ", current->args[i]);
				i++;
			}
		}
		printf("\n");

		// Redirections
		if (current->redirs)
		{
			t_redir *redir = current->redirs;
			printf("  " COLOR_BOLD "Redirs:" COLOR_RESET " ");
			while (redir)
			{
				const char *type_color = COLOR_WHITE;
				if (redir->type == 1 || redir->type == 3)
					type_color = COLOR_YELLOW;
				else if (redir->type == 2 || redir->type == 4)
					type_color = COLOR_MAGENTA;

				printf("%s%s" COLOR_RESET COLOR_BOLD "->" COLOR_RESET
					COLOR_CYAN "%s" COLOR_RESET " ",
					type_color,
					redir_type_to_str(redir->type),
					redir->file);
				redir = redir->next;
			}
			printf("\n");
		}

		if (current->next)
			printf("  " COLOR_BLUE "└── PIPE ──┐" COLOR_RESET "\n");
		current = current->next;
	}

	printf(COLOR_BOLD BG_BLUE COLOR_WHITE "═══════════════════════════════"
		COLOR_RESET "\n\n");
}
