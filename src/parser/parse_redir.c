#include "../includes/minishell.h"

static int	skip_spaces(t_token **tokens)
{
	while (*tokens && (*tokens)->type == SPACES)
		*tokens = (*tokens)->next;
	return (1);
}

static t_redir	*create_valid_redir(t_token **tokens, t_token_type type)
{
	char	*file;
	t_redir	*redir;

	file = ft_strdup((*tokens)->value);
	if (!file)
		return (NULL);
	*tokens = (*tokens)->next;
	redir = create_redir(type, file);
	if (!redir)
	{
		free(file);
		return (NULL);
	}
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
	t_token_type	type;

	if (!tokens || !*tokens)
		return (NULL);
	type = (*tokens)->type;
	*tokens = (*tokens)->next;
	skip_spaces(tokens);
	if (*tokens && ((*tokens)->type == WORD || (*tokens)->type == VAR))
		return (create_valid_redir(tokens, type));
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
