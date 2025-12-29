#include "../../includes/minishell.h"

int	is_command_separator(t_token_type type)
{
	return (type == PIPE);
}

static int	append_arg(t_cmd *cmd, char *value)
{
	char	**new_args;
	char	*dup;
	int		count;
	int		i;

	if (!cmd || !value)
		return (0);
	dup = ft_strdup(value);
	if (!dup)
		return (0);
	count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
			count++;
	}
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (free(dup), 0);
	i = 0;
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[count] = dup;
	new_args[count + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	return (1);
}

static int	handle_initial_redirs(t_token **tokens, t_cmd *cmd, t_shell *shell)
{
	t_redir	*redir;

	while (*tokens
		&& !is_command_separator((*tokens)->type)
		&& is_redir((*tokens)->type))
	{
		redir = parse_redirection(tokens, shell);
		if (!redir)
			return (0);
		add_redir(&cmd->redirs, redir);
		while (*tokens && (*tokens)->type == SPACES)
			*tokens = (*tokens)->next;
	}
	return (1);
}

static int	handle_args(t_token **tokens, t_cmd *cmd)
{
	cmd->args = parse_arguments(tokens);
	if (!cmd->args)
	{
		if (!cmd->redirs)
			return (0);
		cmd->args = malloc(sizeof(char *));
		if (!cmd->args)
			return (0);
		cmd->args[0] = NULL;
	}
	return (1);
}

static int	handle_remaining_redirs(t_token **tokens, t_cmd *cmd,
		t_shell *shell)
{
	t_redir	*redir;

	while (*tokens && !is_command_separator((*tokens)->type))
	{
		if (is_redir((*tokens)->type))
		{
			redir = parse_redirection(tokens, shell);
			if (!redir)
				return (0);
			add_redir(&cmd->redirs, redir);
		}
		else if ((*tokens)->type == WORD)
		{
			if (!append_arg(cmd, (*tokens)->value))
				return (0);
			*tokens = (*tokens)->next;
		}
		else if ((*tokens)->type == SPACES)
			*tokens = (*tokens)->next;
		else
			*tokens = (*tokens)->next;
	}
	return (1);
}

t_cmd	*parse_command(t_token **tokens, t_shell *shell)
{
	t_cmd	*cmd;

	cmd = create_cmd();
	if (!cmd)
		return (NULL);
	if (!handle_initial_redirs(tokens, cmd, shell))
		return (free_cmd(cmd), NULL);
	if (!handle_args(tokens, cmd))
		return (free_cmd(cmd), NULL);
	if (!handle_remaining_redirs(tokens, cmd, shell))
		return (free_cmd(cmd), NULL);
	return (cmd);
}
