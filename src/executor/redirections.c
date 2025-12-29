#include "../../includes/minishell.h"

static void	close_heredoc_fds(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC && redir->fd != -1)
		{
			close(redir->fd);
			redir->fd = -1;
		}
		redir = redir->next;
	}
}

static int	apply_heredoc_redirection(t_redir *redir)
{
	if (redir->fd == -1)
		return (1);
	if (dup2(redir->fd, STDIN_FILENO) == -1)
	{
		handle_dup2_error(redir->fd);
		redir->fd = -1;
		return (1);
	}
	close(redir->fd);
	redir->fd = -1;
	return (0);
}

static int	handle_single_redirection(t_redir *redir)
{
	if (redir->type == REDIR_IN)
		return (handle_input_redirection(redir));
	if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		return (handle_output_redirection(redir, redir->type));
	if (redir->type == REDIR_HEREDOC)
		return (apply_heredoc_redirection(redir));
	return (0);
}

int	setup_redirections(t_cmd *cmd, t_shell *shell)
{
	t_redir	*redir;
	int		status;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC && redir->fd == -1)
		{
			status = handle_heredoc_redirection(redir, shell);
			if (status != 0)
			{
				close_heredoc_fds(cmd->redirs);
				return (status);
			}
		}
		redir = redir->next;
	}
	redir = cmd->redirs;
	while (redir)
	{
		status = handle_single_redirection(redir);
		if (status != 0)
		{
			close_heredoc_fds(cmd->redirs);
			return (status);
		}
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
		if (*saved_stdin != -1)
			close(*saved_stdin);
		if (*saved_stdout != -1)
			close(*saved_stdout);
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
