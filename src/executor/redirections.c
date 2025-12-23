#include "../../includes/minishell.h"

static int	handle_single_redirection(t_redir *redir)
{
	if (redir->type == REDIR_IN)
		return (handle_input_redirection(redir));
	if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		return (handle_output_redirection(redir, redir->type));
	if (redir->type == REDIR_HEREDOC)
		return (handle_heredoc_redirection(redir));
	return (0);
}

int	setup_redirections(t_cmd *cmd)
{
	t_redir	*redir;
	int		status;

	redir = cmd->redirs;
	while (redir)
	{
		status = handle_single_redirection(redir);
		if (status != 0)
			return (status);
		redir = redir->next;
	}
	return (0);
}

int	save_redirections(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdin == -1 || *saved_stdout == -1)
	{
		perror("minishell: dup");
		return (1);
	}
	return (0);
}

int	restore_redirections(int saved_stdin, int saved_stdout)
{
	int	ret;

	ret = 0;
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2 stdin");
		ret = 1;
	}
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2 stdout");
		ret = 1;
	}
	close(saved_stdin);
	close(saved_stdout);
	return (ret);
}
