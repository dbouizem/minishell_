#include "../../includes/minishell.h"

char	*read_input(void)
{
	char	*input;

	input = readline(PROMPT_COLOR "minishell$ " RESET_COLOR);
	if (!input)
	{
		if (errno)
			perror("minishell: readline error");
		return (NULL);
	}
	rl_replace_line("", 0);
	rl_on_new_line();
	if (*input)
		add_history(input);
	return (input);
}

void	display_welcome(void)
{
	printf("%s\n", BLUE);
	printf("┌──────────────────────────────────────────────────┐\n");
	printf("│                 🐚 MINISHELL 🐚                  │\n");
	printf("└──────────────────────────────────────────────────┘\n");
	printf("%s\n", RESET);
}
