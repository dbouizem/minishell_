#include "../includes/minishell.h"

t_redir	*parse_redirection(t_token **tokens)
{
	t_token_type	type;
	char			*file;
	t_redir			*redir;

	if (!tokens || !*tokens)
		return (NULL);
	type = (*tokens)->type;
	*tokens = (*tokens)->next;
	while (*tokens && (*tokens)->type == SPACES)
		*tokens = (*tokens)->next;
	if (*tokens && ((*tokens)->type == WORD || (*tokens)->type == VAR))
	{
		file = ft_strdup((*tokens)->value);
		*tokens = (*tokens)->next;
		redir = create_redir(type, file);
		return (redir);
	}
	else
		return (write(2, "minishell: syntax error near unexpected token\n", 46),
			NULL);
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
