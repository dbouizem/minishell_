#include "../includes/minishell.h"

int	lexer_quote_error(char quote)
{
	printf("minishell: syntax error: unclosed quote `%c'\n", quote);
	return (1);
}

void	lexer_memory_error(char *context)
{
	printf("minishell: lexer error: memory allocation failed for %s\n", context);
}

void	lexer_syntax_error(char *token)
{
	if (token)
		printf("minishell: syntax error near unexpected token `%s'\n", token);
	else
		printf("minishell: syntax error\n");
}

int	has_quote_error(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (is_quote(input[i]))
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				i++;
			if (!input[i])
				return (lexer_quote_error(quote));
			i++;
		}
		else
			i++;
	}
	return (0);
}
