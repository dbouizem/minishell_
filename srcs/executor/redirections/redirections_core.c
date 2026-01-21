#include "../../../includes/minishell.h"

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

static int	prepare_heredocs(t_cmd *cmd, t_shell *shell)
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
				return (status);
		}
		redir = redir->next;
	}
	return (0);
}

int	setup_redirections(t_cmd *cmd, t_shell *shell)
{
	t_redir	*redir;
	int		status;

	status = prepare_heredocs(cmd, shell);
	if (status != 0)
	{
		close_heredoc_fds(cmd->redirs);
		return (status);
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
