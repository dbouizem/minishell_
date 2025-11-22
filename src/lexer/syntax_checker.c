#include "../includes/minishell.h"

static int	check_pipe_errors(t_token *current)
{
	if (current->type == PIPE && current->next
		&& current->next->type == PIPE)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	if (current->type == PIPE && !current->next)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}

static int	check_redir_errors(t_token *current)
{
	if (is_redir(current->type)
		&& (!current->next || current->next->type == PIPE))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}

static int	check_pipe_start(t_token *tokens)
{
	if (tokens->type == PIPE)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}

int	check_syntax_errors(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return (1);
	current = tokens;
	if (!check_pipe_start(current))
		return (0);
	while (current)
	{
		if (!check_pipe_errors(current))
			return (0);
		if (!check_redir_errors(current))
			return (0);
		current = current->next;
	}
	return (1);
}

