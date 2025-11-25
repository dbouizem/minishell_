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

char	*read_input_non_interactive(void)
{
	char	*line;
	size_t	len;

	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

void	display_welcome(void)
{
	printf("%s\n", BLUE);
	printf("┌──────────────────────────────────────────────────┐\n");
	printf("│                 🐚 MINISHELL 🐚                  │\n");
	printf("└──────────────────────────────────────────────────┘\n");
	printf("%s\n", RESET);
}
