#include "../includes/minishell.h"

int	handle_triple_redir(char *input, int i)
{
	if ((input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '>')
		|| (input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<'))
	{
		printf("minishell: syntax error near unexpected token `%c'\n",
			input[i]);
		return (1);
	}
	return (0);
}

static void	handle_triple_redir_tokens(char *input, int *i,
	t_token **head, t_token **curr)
{
	char	*value;
	t_token	*token;
	int		len;

	len = 1;
	while (len <= 3 && (input[*i] == '>' || input[*i] == '<'))
	{
		value = extract_substring(input, *i, *i + 1);
		if (value)
		{
			token = create_token(get_redir_type(input, *i), value);
			if (token)
				add_token(head, curr, token);
			else
				free(value);
		}
		(*i)++;
		len++;
	}
}

static void	create_single_redir_token(char *input, int *i,
	t_token **head, t_token **curr)
{
	t_token_type	type;
	char			*value;
	int				len;
	t_token			*token;

	type = get_redir_type(input, *i);
	if (type == HEREDOC || type == APPEND)
		len = 2;
	else
		len = 1;
	value = extract_substring(input, *i, *i + len);
	*i += len;
	if (!value)
		return ;
	token = create_token(type, value);
	if (!token)
		free(value);
	else
		add_token(head, curr, token);
}

void	create_redir_token(char *input, int *i, t_token **head, t_token **curr)
{
	if (handle_triple_redir(input, *i))
		handle_triple_redir_tokens(input, i, head, curr);
	else
		create_single_redir_token(input, i, head, curr);
}
