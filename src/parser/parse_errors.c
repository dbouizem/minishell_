#include "../../includes/minishell.h"

void	parse_syntax_error(t_token **tokens, t_shell *shell)
{
	if (*tokens && is_redir((*tokens)->type))
	{
		printf("minishell: syntax error near unexpected token `%c'\n",
			(*tokens)->value[0]);
	}
	else if (*tokens)
	{
		printf("minishell: syntax error near unexpected token `%s'\n",
			(*tokens)->value);
	}
	else
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
	}
	shell->exit_status = 2;
}

void	pipe_syntax_error(t_shell *shell)
{
	printf("minishell: syntax error near unexpected token `|'\n");
	shell->exit_status = 2;
}

void	redir_syntax_error(t_shell *shell)
{
	printf("minishell: syntax error near unexpected token `newline'\n");
	shell->exit_status = 2;
}

int	parse_memory_error(char *context)
{
	printf("minishell: parse error: %s %s\n",
		"memory allocation failed for", context);
	return (0);
}
