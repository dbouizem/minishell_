#include "../includes/minishell.h"

t_cmd	*parse_command(t_token **tokens)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = create_cmd();
	if (!cmd)
		return (NULL);
	cmd->args = parse_arguments(tokens);
	if (!cmd->args)
		return (free_cmd(cmd), NULL);
	while (*tokens && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == INPUT || (*tokens)->type == TRUNC
			|| (*tokens)->type == HEREDOC || (*tokens)->type == APPEND)
		{
			redir = parse_redirection(tokens);
			if (!redir)
				return (free_cmd(cmd), NULL);
			add_redir(&cmd->redirs, redir);
		}
		else if ((*tokens)->type == SPACES)
			*tokens = (*tokens)->next;
		else
			*tokens = (*tokens)->next;
	}
	return (cmd);
}
