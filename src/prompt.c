#include "minishell.h"
#include "colors.h"

void	display_prompt(void)
{
	write(1, PROMPT_COLOR "minishell$ " RESET_COLOR,
		sizeof(PROMPT_COLOR "minishell$ " RESET_COLOR) - 1);
}
