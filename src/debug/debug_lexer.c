#include "../../includes/minishell.h"

void	print_tokens(t_token *tokens)
{
	const char	*names[] = {
		"", "SPACES", "WORD", "VAR", "PIPE",
		"INPUT", "TRUNC", "HEREDOC", "APPEND", "INVALID", "END"
	};
	const char	*val;

	printf("\n=== TOKENS ===\n");
	while (tokens)
	{
		val = tokens->value;
		if (!val)
			val = "(null)";
		printf("%-10s | '%s'\n",
			names[tokens->type],
			val);
		tokens = tokens->next;
	}
	printf("==============\n\n");
}
