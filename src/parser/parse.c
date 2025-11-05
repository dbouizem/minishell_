#include "../includes/minishell.h"

static void	add_command_to_list(t_cmd **head, t_cmd **current, t_cmd *new_cmd)
{
	if (!*head)
	{
		*head = new_cmd;
		*current = *head;
	}
	else
	{
		(*current)->next = new_cmd;
		*current = (*current)->next;
	}
}

static void	skip_pipe_token(t_token **tokens)
{
	if (*tokens && (*tokens)->type == PIPE)
		*tokens = (*tokens)->next;
}

t_cmd	*parse(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current;
	t_cmd	*new_cmd;

	head = NULL;
	current = NULL;
	if (!tokens)
		return (NULL);
	while (tokens)
	{
		new_cmd = parse_command(&tokens);
		if (!new_cmd)
			break ;
		add_command_to_list(&head, &current, new_cmd);
		skip_pipe_token(&tokens);
	}
	return (head);
}
