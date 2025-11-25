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
	ssize_t	read_bytes;

	line = NULL;
	len = 0;
	read_bytes = getline(&line, &len, stdin);
	if (read_bytes == -1)
	{
		if (line)
			free(line);
		return (NULL);
	}
	if (read_bytes > 0 && line[read_bytes - 1] == '\n')
		line[read_bytes - 1] = '\0';
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
