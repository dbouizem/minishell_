#include "../includes/minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
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

/* int	is_valid_vars_char(char c)
{
	return (c == '_'
		|| (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'));
} */
