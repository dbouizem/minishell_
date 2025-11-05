#include "../includes/minishell.h"

char	*read_input(void)
{
	char	*input;

	input = readline(PROMPT_COLOR "minishell$ " RESET_COLOR);
	if (!input)
	{
		printf("%sexit%s\n", RED, RESET);
		return (NULL);
	}
	if (*input)
		add_history(input);
	return (input);
}

int	handle_input(char *input, t_shell *shell)
{
	if (!input)
		return (0);
	if (input[0] == '\0')
	{
		free(input);
		return (1);
	}
	if (ft_strcmp(input, "exit") == 0)
	{
		free(input);
		cleanup_shell(shell);
		exit(shell->exit_status);
	}
	return (2);
}
