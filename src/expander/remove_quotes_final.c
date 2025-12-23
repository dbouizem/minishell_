#include "../../includes/minishell.h"

static void	remove_quotes_from_redirections(t_cmd *current)
{
	t_redir	*redir;
	char	*cleaned;

	redir = current->redirs;
	while (redir)
	{
		if (redir->type != REDIR_HEREDOC && redir->file)
		{
			cleaned = remove_quotes(redir->file);
			if (cleaned)
			{
				free(redir->file);
				redir->file = cleaned;
			}
		}
		redir = redir->next;
	}
}

static void	remove_quotes_from_args(t_cmd *current)
{
	int		i;
	char	*cleaned;

	if (current->args)
	{
		i = 0;
		while (current->args[i])
		{
			cleaned = remove_quotes(current->args[i]);
			if (cleaned)
			{
				free(current->args[i]);
				current->args[i] = cleaned;
			}
			i++;
		}
	}
}

void	remove_quotes_from_command(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		remove_quotes_from_args(current);
		remove_quotes_from_redirections(current);
		current = current->next;
	}
}
