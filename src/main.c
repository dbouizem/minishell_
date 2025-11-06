#include "../includes/minishell.h"

static void	process_input(char *input, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;

	// LEXER
	tokens = tokenize(input);
	if (tokens)
	{
		printf("\n%s LEXER OUTPUT:%s\n", BLUE, RESET);
		print_tokens(tokens);
	}

	// PARSER
	cmds = parse(tokens);
	if (cmds)
	{
		printf("\n%s PARSER OUTPUT:%s\n", GREEN, RESET);
		print_cmd(cmds);

	// EXPANDER
		expand_commands(cmds, shell);
		printf("\n%s AFTER EXPANSION:%s\n", MAGENTA, RESET);
		print_cmd(cmds);

		free_cmd(cmds);
	}
	if (tokens)
		free_tokens(tokens);
}

int	handle_input(char *input, t_shell *shell)
{
	if (input[0] == '\0')
		return (0);
	if (ft_strcmp(input, "exit") == 0)
		return (1);
	process_input(input, shell);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*input;
	int		should_exit;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);

	while (1)
	{
		input = read_input();
		if (!input)
			break ;

		should_exit = handle_input(input, &shell);
		free(input);

		if (should_exit)
			break ;
	}
	cleanup_shell(&shell);
	return (shell.exit_status);
}
