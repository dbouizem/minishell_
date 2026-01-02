#include "../includes/minishell.h"

static int	skip_spaces(t_token **tokens)
{
	while (*tokens && (*tokens)->type == SPACES)
		*tokens = (*tokens)->next;
	return (1);
}

static t_redir	*create_valid_redir(t_token **tokens, t_token_type token_type)
{
	char			*file;
	t_redir			*redir;
	t_redir_type	redir_type;

	if (token_type == INPUT)		// INPUT = 5 (token)
		redir_type = REDIR_IN;		// REDIR_IN = 1 (redir)
	else if (token_type == TRUNC)	// TRUNC = 6
		redir_type = REDIR_OUT;		// REDIR_OUT = 2
	else if (token_type == APPEND)	// APPEND = 8
		redir_type = REDIR_APPEND;	// REDIR_APPEND = 3
	else if (token_type == HEREDOC)	// HEREDOC = 7
		redir_type = REDIR_HEREDOC;	// REDIR_HEREDOC = 4
	else
	{
		printf("minishell: internal parser error\n");
		return (NULL);
	}
	file = ft_strdup((*tokens)->value);
	if (!file)
		return (NULL);
	*tokens = (*tokens)->next;
	redir = create_redir(redir_type, file);
	if (!redir)
		return (free(file), NULL);
	return (redir);
}

static void	handle_syntax_error(t_token **tokens, t_shell *shell)
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

t_redir	*parse_redirection(t_token **tokens, t_shell *shell)
{
	t_token_type	token_type;

	if (!tokens || !*tokens)
		return (NULL);
	token_type = (*tokens)->type;
	*tokens = (*tokens)->next;
	skip_spaces(tokens);
	if (*tokens && (*tokens)->type == WORD)
		return (create_valid_redir(tokens, token_type));
	else
	{
		handle_syntax_error(tokens, shell);
		return (NULL);
	}
}

void	add_redir(t_redir **head, t_redir *new_redir)
{
	t_redir	*current;

	if (!*head)
	{
		*head = new_redir;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}
