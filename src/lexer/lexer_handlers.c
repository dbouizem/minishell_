#include "../includes/minishell.h"

char	*extract_substring(char *input, int start, int end)
{
	char	*str;
	int		len;
	int		i;

	len = end - start;
	if (len <= 0)
		return (NULL);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = input[start++];
	str[i] = '\0';
	return (str);
}

int	handle_quotes(char *input, int *i)
{
	char	quote_type;

	quote_type = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote_type)
		(*i)++;
	if (!input[*i])
	{
		printf("minishell: unclosed quote `%c'\n", quote_type);
		return (0);
	}
	(*i)++;
	return (1);
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
	if (token)
		add_token(head, current, token);
	else
		free(spaces);
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
		{
			word = ft_strdup("");
			if (!word)
				return ;
		}
		else
			return ;
	}
	token = create_token(WORD, word);
	if (!token)
		free(word);
	else
		add_token(head, current, token);
}
