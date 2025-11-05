#include "../includes/minishell.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token **current, t_token *new_token)
{
	if (!*head)
	{
		*head = new_token;
		*current = *head;
	}
	else
	{
		(*current)->next = new_token;
		*current = (*current)->next;
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	print_tokens(t_token *tokens)
{
	const char	*names[] = {
		"", "SPACES", "WORD", "VAR", "PIPE",
		"INPUT", "TRUNC", "HEREDOC", "APPEND", "END"
	};
	const char	*val;

	printf("\n=== TOKENS ===\n");
	while (tokens)
	{
		val = tokens->value;
		if (!val)
			val = "(null)";
		printf("%-10s | '%s'\n",
			names[tokens->type],
			val);
		tokens = tokens->next;
	}
	printf("==============\n\n");
}

