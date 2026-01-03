#include "../includes/minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_redir(t_token_type type)
{
	return (type == INPUT || type == TRUNC
		|| type == HEREDOC || type == APPEND);
}

int	is_forbidden_char(char c)
{
	if (c == '\\')
		return (1);
	if (c == ';')
		return (1);
	if (c >= 0 && c <= 31)
		return (1);
	if (c == 127)
		return (1);
	return (0);
}
