#include "../includes/minishell.h"

static int	check_sep_syntax(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*current;
	const char	*op_names[] = {"", "", "", "", "|", "&&", "||"};

	if (!cmds)
		return (1);
	current = cmds;
	while (current && current->next)
		current = current->next;
	if (current && (!current->args || !current->args[0]))
<<<<<<< HEAD
	{
		if (current->separator)
			printf("minishell: syntax error near unexpected token %s\n", op_names[current->separator]);
		else
			printf("minishell: syntax error near unexpected token `newline'\n");
		shell->exit_status = 2;
		return (0);
	}
=======
		return (pipe_syntax_error(shell), 0);

>>>>>>> origin/5-exec
	current = cmds;
	while (current)
	{
		if (!current->args || !current->args[0])
<<<<<<< HEAD
		{
			if (current->separator)
				printf("minishell: syntax error near unexpected token `%s'\n",
					op_names[current->separator]);
			shell->exit_status = 2;
			return (0);
		}
=======
			return (pipe_syntax_error(shell), 0);
>>>>>>> origin/5-exec
		current = current->next;
	}
	return (1);
}

static int	check_redir_syntax(t_cmd *cmds, t_shell *shell)
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
				return (redir_syntax_error(shell), 0);
			current_redir = current_redir->next;
		}
		current_cmd = current_cmd->next;
	}
	return (1);
}

int	check_parser_syntax(t_token *tokens, t_cmd *cmds, t_shell *shell)
{
	if (!tokens || !cmds)
		return (1);
	if (!check_sep_syntax(cmds, shell))
		return (0);
	if (!check_redir_syntax(cmds, shell))
		return (0);
	return (1);
}
