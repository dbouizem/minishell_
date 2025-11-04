#include "minishell.h"
#include "colors.h"

char	*read_input(void)
{
	char	*input;

	input = readline("");
	if (!input)
	{
		printf("%sexit%s\n", RED, RESET);
		return (NULL);
	}
	if (*input)
		add_history(input);
	return (input);
}
