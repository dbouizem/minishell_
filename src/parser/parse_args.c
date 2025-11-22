#include "../includes/minishell.h"

int	count_args(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == WORD || tokens->type == VAR)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

static void	free_args_until(char **args, int i)
{
	while (i > 0)
		free(args[--i]);
	free(args);
}

static int	process_argument(t_token **tokens, char **args, int *i)
{
	if ((*tokens)->type == WORD || (*tokens)->type == VAR)
	{
		args[*i] = ft_strdup((*tokens)->value);
		if (!args[*i])
			return (0);
		(*i)++;
		*tokens = (*tokens)->next;
	}
	else if (is_redir((*tokens)->type))
		return (2);
	else
		*tokens = (*tokens)->next;
	return (1);
}

static char	**process_arguments(t_token **tokens, int count)
{
	char	**args;
	int		i;
	int		result;

	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (*tokens && (*tokens)->type != PIPE && i < count)
	{
		result = process_argument(tokens, args, &i);
		if (result == 0)
			return (free_args_until(args, i), NULL);
		if (result == 2)
			break ;
	}
	args[i] = NULL;
	return (args);
}

char	**parse_arguments(t_token **tokens)
{
	char	**args;
	int		count;

	count = count_args(*tokens);
	if (count == 0)
	{
		args = malloc(sizeof(char *));
		if (!args)
			return (NULL);
		args[0] = NULL;
		return (args);
	}
	return (process_arguments(tokens, count));
}
