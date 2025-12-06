#include "../includes/minishell.h"

char	*extract_substring(char *input, int start, int end)
{
	int	len;

	len = end - start;
	if (len <= 0)
		return (NULL);
	return (ft_substr(input, start, len));
}

void	handle_spaces(char *input, int *i, t_token **head, t_token **current)
{
	int		start;
	char	*spaces;
	t_token	*token;

	start = *i;
	while (input[*i] && is_whitespace(input[*i]))
		(*i)++;
	if (start == *i)
		return ;
	spaces = extract_substring(input, start, *i);
	if (!spaces)
		return ;
	token = create_token(SPACES, spaces);
	if (!token)
		free(spaces);
	else
		add_token(head, current, token);
}

void	handle_word(char *input, int *i, t_token **head, t_token **current)
{
	char	*word;
	t_token	*token;
	int		start_index;

	start_index = *i;
	word = extract_word_without_quotes(input, i);
	if (!word)
	{
		if (*i > start_index)
			word = ft_strdup("");
		if (!word)
			return ;
	}
	token = create_token(WORD, word);
	if (!token)
		free(word);
	else
		add_token(head, current, token);
}
