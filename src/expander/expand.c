#include "../includes/minishell.h"

void	expand_commands(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	*expanded;
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
					free(cmd->args[i]);
					cmd->args[i] = expanded;
				}
				i++;
			}
		}
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type != HEREDOC && redir->file)
			{
				expanded = expand_string(redir->file, shell);
				if (expanded)
				{
					free(redir->file);
					redir->file = expanded;
				}
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
