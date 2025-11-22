#include "../includes/minishell.h"

t_token_type	get_redir_type(char *input, int i)
{
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			return (HEREDOC);
		return (INPUT);
	}
	else if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			return (APPEND);
		return (TRUNC);
	}
	return (WORD);
}

static void	create_pipe_token(t_token **head, t_token **current, int *i)
{
	char	*value;
	t_token	*token;

	value = malloc(2);
	if (!value)
		return ;
	value[0] = '|';
	value[1] = '\0';
	token = create_token(PIPE, value);
	if (token)
		add_token(head, current, token);
	else
		free(value);
	(*i)++;
}

void	handle_pipe_or_redir(char *input, int *i, t_token **head,
		t_token **current)
{
	if (input[*i] == '|')
		create_pipe_token(head, current, i);
	else
		create_redir_token(input, i, head, current);
}
