#include "../../includes/minishell.h"

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

	if (token_type == INPUT)
		redir_type = REDIR_IN;
	else if (token_type == TRUNC)
		redir_type = REDIR_OUT;
	else if (token_type == APPEND)
		redir_type = REDIR_APPEND;
	else if (token_type == HEREDOC)
		redir_type = REDIR_HEREDOC;
	else
	{
		ft_putendl_fd("minishell: internal parser error", STDERR_FILENO);
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
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putchar_fd((*tokens)->value[0], STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
	}
	else if (*tokens)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putstr_fd((*tokens)->value, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
	}
	else
	{
		ft_putendl_fd(
			"minishell: syntax error near unexpected token `newline'",
			STDERR_FILENO);
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
