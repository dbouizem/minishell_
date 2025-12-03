#include "../includes/minishell.h"

void	remove_quotes_from_command(t_cmd *cmd)
{
	t_cmd	*current;
	t_redir	*redir;
	int		i;
	char	*cleaned;

	current = cmd;
	while (current)
	{
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

		// Redirections (sauf heredoc)
		redir = current->redirs;
		while (redir)
		{
			if (redir->type != HEREDOC && redir->file)
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
		current = current->next;
	}
}
