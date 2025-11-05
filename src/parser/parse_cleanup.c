#include "../includes/minishell.h"

void	free_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs)
	{
		tmp = redirs;
		redirs = redirs->next;
		if (tmp->file)
			free(tmp->file);
		free(tmp);
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->args)
		{
			i = 0;
			while (tmp->args[i])
				free(tmp->args[i++]);
			free(tmp->args);
		}
		free_redirs(tmp->redirs);
		free(tmp);
	}
}
