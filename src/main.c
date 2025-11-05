#include "minishell.h"

static void	process_input(char *input)
{
	t_token	*tokens;
	t_cmd	*cmds;

	printf("\n%s[DEBUG] Input: %s%s\n", YELLOW, input, RESET);
	tokens = tokenize(input);
	if (!tokens)
	{
		printf("%s[ERROR] Tokenization failed%s\n", RED, RESET);
		return ;
	}
	print_tokens(tokens);
	cmds = parse(tokens);
	if (cmds)
	{
		print_cmd(cmds);
		free_cmd(cmds);
	}
	else
		printf("%s[ERROR] Parsing failed%s\n", RED, RESET);
	free_tokens(tokens);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*input;
	int		status;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	while (1)
	{
		input = read_input();
		status = handle_input(input, &shell);
		if (status == 0)
			break ;
		if (status == 1)
			continue ;
		process_input(input);
		free(input);
	}
	cleanup_shell(&shell);
	return (shell.exit_status);
}
