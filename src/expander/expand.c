#include "../includes/minishell.h"

void	expand_commands(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	*expanded;
	char	*no_quotes;
	t_redir	*redir;

	while (cmd)
	{
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				expanded = expand_string(cmd->args[i], shell);
				if (expanded)
				{
					no_quotes = remove_quotes(expanded);
					free(cmd->args[i]);
					free(expanded);
					cmd->args[i] = no_quotes;
				}
				i++;
			}
		}
		redir = cmd->redirs;
		while (redir)
		{
			expanded = expand_string(redir->file, shell);
			if (expanded)
			{
				no_quotes = remove_quotes(expanded);
				free(redir->file);
				free(expanded);
				redir->file = no_quotes;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
