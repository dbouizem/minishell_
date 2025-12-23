#include "../../includes/minishell.h"

/* Erreur de quote non fermée */
int	lexer_quote_error(char quote)
{
	printf("minishell: syntax error: unclosed quote `%c'\n", quote);
	return (1);
}

/* Erreur d'allocation mémoire */
void	lexer_memory_error(char *context)
{
	printf("minishell: lexer error: memory allocation failed for %s\n", context);
}

/* Erreur de syntaxe générale */
void	lexer_syntax_error(char *token)
{
	if (token)
		printf("minishell: syntax error near unexpected token `%s'\n", token);
	else
		printf("minishell: syntax error\n");
}

/* Vérification quotes avec gestion erreur améliorée */
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
