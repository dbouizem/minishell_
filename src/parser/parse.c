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

static int	check_final_pipe(t_token *tokens, t_cmd *head, t_shell *shell)
{
	if (tokens && tokens->type == PIPE && !tokens->next)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		shell->exit_status = 2;
		free_cmd(head);
		return (0);
	}
	return (1);
}

static t_cmd	*process_tokens(t_token *tokens, t_shell *shell)
{
	t_cmd	*head;
	t_cmd	*current;
	t_cmd	*new_cmd;

	head = NULL;
	current = NULL;
	while (tokens)
	{
		new_cmd = parse_command(&tokens, shell);
		if (!new_cmd)
		{
			if (head)
				free_cmd(head);
			return (NULL);
		}
		add_command_to_list(&head, &current, new_cmd);
		if (!check_final_pipe(tokens, head, shell))
			return (NULL);
		skip_pipe_token(&tokens);
	}
	return (head);
}

t_cmd	*parse(t_token *tokens, t_shell *shell)
{
	t_cmd	*head;

	if (!tokens)
		return (NULL);
	head = process_tokens(tokens, shell);
	if (!head)
		return (NULL);
	if (!check_parser_syntax(head, shell))
	{
		free_cmd(head);
		return (NULL);
	}
	return (head);
}
