#include "../../includes/minishell.h"

static int	handle_exit_command(t_cmd *cmds)
{
	if (cmds->args && ft_strcmp(cmds->args[0], "exit") == 0)
	{
		printf("%sExiting minishell...%s\n", YELLOW, RESET);
		return (1);
	}
	return (0);
}

static void	debug_lexer_parser(t_token *tokens, t_cmd *cmds, t_shell *shell)
{
	 (void)tokens;
	(void)shell;
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
}

static int	is_only_whitespace(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	process_input(char *input, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;
	int		should_exit;

	if (!input || input[0] == '\0' || is_only_whitespace(input))
		return (0);
	tokens = NULL;
	cmds = NULL;
	should_exit = 0;
	tokens = tokenize(input);
	if (!tokens)
	{
		shell->exit_status = 2;
		return (0);
	}
	cmds = parse(tokens, shell);
	if (!cmds)
	{
		if (tokens)
			free_tokens(tokens);
		return (0);
	}
	expand_commands(cmds, shell);
	should_exit = handle_exit_command(cmds);
	if (should_exit)
	{
		debug_lexer_parser(tokens, cmds, shell);
	}
	execute_commands(cmds, shell);
	if (cmds)
		free_cmd(cmds);
	if (tokens)
		free_tokens(tokens);

	return (should_exit);
}
