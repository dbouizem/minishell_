#include "../includes/minishell.h"

void	get_ope_value(t_token_type type, char *value, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (type == OR)
			value[i] = '|';
		else if (type == AND || type == INVALID)
			value[i] = '&';
		i++;
	}
	value[len] = '\0';
}

void	create_operator_token(t_token_type type, t_token **head,
	t_token **current, int *i)
{
	char	*value;
	int		len;
	t_token	*token;

	if (type == OR || type == AND)
		len = 2;
	else
		len = 1;
	value = malloc(len + 1);
	if (!value)
		return ;
	get_ope_value(type, value, len);
	token = create_token(type, value);
	if (!token)
		return (free(value));
	add_token(head, current, token);
	*i += len ;
}
