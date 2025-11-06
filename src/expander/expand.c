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
				free(cmd->args[i]);
				cmd->args[i] = expanded;
				i++;
			}
		}
		redir = cmd->redirs;
		while (redir)
		{
			expanded = expand_string(redir->file, shell);
			free(redir->file);
			redir->file = expanded;
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
