#include "../../includes/minishell.h"

void	debug_lexer_parser(t_token *tokens, t_cmd *cmds, t_shell *shell)
{
	// (void)tokens;
	// (void)shell;
	// (void)cmds;

	// LEXER
	if (tokens)
	{
		printf("\n%s LEXER OUTPUT:%s\n", BLUE, RESET);
		print_tokens(tokens);
	}
 	// PARSER
	if (cmds)
	{
		printf("\n%s PARSER OUTPUT:%s\n", YELLOW, RESET);
		print_cmd(cmds);
	}
	// EXPANDER
	if (cmds && !handle_exit_command(cmds))
	{
		expand_commands(cmds, shell);
		printf("\n%s AFTER EXPANSION:%s\n", MAGENTA, RESET);
		print_cmd(cmds);
	}
	// Exécuter
		if (cmds && !handle_exit_command(cmds))
	{
		execute(cmds, shell);
		printf("\n%s AFTER EXECUTION - Exit status: %d%s\n",
			MAGENTA, shell->exit_status, RESET);
	}
}
