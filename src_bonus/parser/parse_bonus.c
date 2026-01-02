#include "../../includes/minishell.h"

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

static void	set_separator(t_cmd *cmd, t_token **tokens)
{
	if (*tokens && is_separator(*tokens))
	{
		cmd->separator = (*tokens)->type;
		*tokens = (*tokens)->next;
		while (*tokens && (*tokens)->type == SPACES)
			*tokens = (*tokens)->next;
	}
	else
		cmd->separator = 0;
}

static int	check_separator_syntax(t_token *tokens)
{
	const char	*op_name[] = {"", "", "", "&&", "||", "|"};

	if (tokens && is_separator(tokens) && !tokens->next)
	{
		printf("minishell: syntax error near unexpected token ");
		printf("`%s'\n", op_name[tokens->type]);
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
		if (!check_separator_syntax(tokens))
			return (free_cmd(head), NULL);
		new_cmd = parse_command(&tokens, shell);
		if (!new_cmd)
			return (free_cmd(head), NULL);
		set_separator(new_cmd, &tokens);
		add_command_to_list(&head, &current, new_cmd);
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
	if (!check_parser_syntax(tokens, head, shell))
		return (free_cmd(head), NULL);
	return (head);
}
