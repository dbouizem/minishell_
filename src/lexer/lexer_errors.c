#include "../../includes/minishell.h"

/* Erreur de quote non fermée */
int	lexer_quote_error(char quote)
{
	ft_putstr_fd("minishell: syntax error: unclosed quote `",
		STDERR_FILENO);
	ft_putchar_fd(quote, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	return (1);
}

/* Erreur d'allocation mémoire */
void	lexer_memory_error(char *context)
{
	ft_putstr_fd("minishell: lexer error: memory allocation failed for ",
		STDERR_FILENO);
	ft_putendl_fd(context, STDERR_FILENO);
}

/* Erreur de syntaxe générale */
void	lexer_syntax_error(char *token)
{
	if (token)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putstr_fd(token, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
	}
	else
		ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
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
