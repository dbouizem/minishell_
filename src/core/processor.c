#include "../../includes/minishell.h"

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

	if (!input)
		return (0);
	if (input[0] == '\0' || is_only_whitespace(input))
		return (0);
	tokens = tokenize(input);
	if (!tokens)
	{
		shell->exit_status = 2;
		return (0);
	}
	cmds = parse(tokens, shell);
	free_tokens(tokens);
	if (!cmds)
		return (0);
	if (g_signal == 1)
	{
		free_cmd(cmds);
		shell->exit_status = 130;
		return (0);
	}
	execute(cmds, shell);
	return (free_cmd(cmds), 0);
}
