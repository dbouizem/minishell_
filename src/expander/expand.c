#include "../../includes/minishell.h"

void	expand_args(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	*expanded;

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

void	expand_redirs(t_redir *redir, t_shell *shell)
{
	char	*expanded;

	while (redir)
	{
		if (redir->type != REDIR_HEREDOC && redir->file)
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
}

void	expand_commands(t_cmd *cmd, t_shell *shell)
{
	while (cmd)
	{
		if (cmd->args)
			expand_args(cmd, shell);
		if (cmd->redirs)
			expand_redirs(cmd->redirs, shell);
		cmd = cmd->next;
	}
}
