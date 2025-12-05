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
	tokens = tokenize(input);
	if (!tokens)
		return (shell->exit_status = 2, 0);
	cmds = parse(tokens, shell);
	if (!cmds)
		return (free_tokens(tokens), 0);
	should_exit = handle_exit_command(cmds);
	if (!should_exit)
		execute(cmds, shell);
	free_cmd(cmds);
	free_tokens(tokens);
	return (should_exit);
}
