#include "../../includes/minishell.h"

/* void	debug_fork_header(int total_cmds)
{
	fprintf(stderr, "\n=== DEBUG fork_all_commands ===\n");
	fprintf(stderr, "Nombre de commandes à forker: %d\n", total_cmds);
}

void	debug_fork_command(int index, t_cmd *cmd)
{
	fprintf(stderr, "Command %d: ", index);
	if (cmd && cmd->args && cmd->args[0])
		fprintf(stderr, "'%s'", cmd->args[0]);
	else
		fprintf(stderr, "(null)");
	fprintf(stderr, "\n");
}

void	debug_fork_parent(int index, pid_t pid)
{
	fprintf(stderr, "  Parent: fork réussi pour cmd %d, pid=%d\n",
		index, pid);
}

void	debug_fork_footer(void)
{
	fprintf(stderr, "=== Fin fork_all_commands ===\n\n");
}
 */


 #include "../../includes/minishell.h"

void	debug_fork_header(int total_cmds)
{
	fprintf(stderr, "\n%s%s=== DEBUG fork_all_commands ===%s\n",
		COLOR_BOLD, COLOR_CYAN, COLOR_RESET);
	fprintf(stderr, "%sNombre de commandes à forker: %s%d%s\n",
		COLOR_YELLOW, COLOR_BOLD, total_cmds, COLOR_RESET);
}

void	debug_fork_command(int index, t_cmd *cmd)
{
	fprintf(stderr, "%s%sCommand %d:%s ",
		COLOR_BOLD, COLOR_MAGENTA, index, COLOR_RESET);
	if (cmd && cmd->args && cmd->args[0])
		fprintf(stderr, "%s'%s'%s", COLOR_GREEN, cmd->args[0], COLOR_RESET);
	else
		fprintf(stderr, "%s(null)%s", COLOR_RED, COLOR_RESET);
	fprintf(stderr, "\n");
}

void	debug_fork_parent(int index, pid_t pid)
{
	fprintf(stderr, "  %s✓ Parent:%s fork réussi pour cmd %s%d%s, pid=%s%d%s\n",
		COLOR_GREEN, COLOR_RESET,
		COLOR_CYAN, index, COLOR_RESET,
		COLOR_YELLOW, pid, COLOR_RESET);
}

void	debug_fork_footer(void)
{
	fprintf(stderr, "%s%s=== Fin fork_all_commands ===%s\n\n",
		COLOR_BOLD, COLOR_CYAN, COLOR_RESET);
}
