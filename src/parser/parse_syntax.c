#include "../includes/minishell.h"

static int	check_pipe_syntax(t_cmd *cmds)
{
	t_cmd	*current;

	if (!cmds)
		return (1);
	current = cmds;
	while (current && current->next)
		current = current->next;

	if (current && (!current->args || !current->args[0]))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	current = cmds;
	while (current)
	{
		if (!current->args || !current->args[0])
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (0);
		}
		current = current->next;
	}
	return (1);
}

static int	check_redir_syntax(t_cmd *cmds)
{
	t_cmd		*current_cmd;
	t_redir		*current_redir;

	current_cmd = cmds;
	while (current_cmd)
	{
		current_redir = current_cmd->redirs;
		while (current_redir)
		{
			if (!current_redir->file || current_redir->file[0] == '\0')
			{
				printf("minishell: syntax error near "
					"unexpected token `newline'\n");
				return (0);
			}
			current_redir = current_redir->next;
		}
		current_cmd = current_cmd->next;
	}
	return (1);
}

int	check_parser_syntax(t_cmd *cmds)
{
	if (!cmds)
		return (1);

	if (!check_pipe_syntax(cmds))
		return (0);

	if (!check_redir_syntax(cmds))
		return (0);

	return (1);
}
