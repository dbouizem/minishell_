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

static int	should_copy_char(char c, char *quote)
{
	if (c == '\'' || c == '\"')
	{
		if (*quote == 0)
			*quote = c;
		else if (*quote == c)
			*quote = 0;
		else
			return (1);
		return (0);
	}
	return (1);
}

char	*remove_quote(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*res;

	if (!str)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if (should_copy_char(str[i], &quote))
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}
