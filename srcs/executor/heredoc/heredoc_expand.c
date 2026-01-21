#include "../../../includes/minishell.h"

static int	append_part(char **result, char *part)
{
	char	*new_result;

	if (!part)
		return (free(*result), 0);
	new_result = ft_strjoin_free(*result, part);
	free(part);
	if (!new_result)
		return (0);
	*result = new_result;
	return (1);
}

char	*expand_heredoc_line(char *line, t_shell *shell)
{
	char	*result;
	char	*part;
	int		i;

	if (!line)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			part = process_dollar(line, &i, shell);
		else
			part = char_to_str(line[i++]);
		if (!append_part(&result, part))
			return (NULL);
	}
	return (result);
}

char	*heredoc_append_char(char *line, size_t *len, size_t *cap, char c)
{
	size_t	new_cap;
	char	*new_line;

	if (*len + 2 > *cap)
	{
		new_cap = *cap * 2;
		if (new_cap < 64)
			new_cap = 64;
		while (new_cap < *len + 2)
			new_cap *= 2;
		new_line = malloc(new_cap);
		if (!new_line)
			return (free(line), NULL);
		if (line)
			ft_memcpy(new_line, line, *len);
		free(line);
		line = new_line;
		*cap = new_cap;
	}
	line[*len] = c;
	(*len)++;
	return (line);
}

char	*heredoc_finalize_line(char *line, size_t len, ssize_t n)
{
	if (n == 0 && len == 0)
		return (free(line), NULL);
	if (!line)
		return (ft_strdup(""));
	line[len] = '\0';
	return (line);
}
