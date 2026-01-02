#include "../includes/minishell.h"

t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_redir	*create_redir(t_redir_type type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
	{
		free(file);
		return (NULL);
	}
	redir->type = type;
	redir->file = file;
	redir->next = NULL;
	return (redir);
}

int	is_separator(t_token *token)
{
	if (!token)
		return (0);
	return (is_command_separator(token->type));
}