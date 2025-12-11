#include "../includes/minishell.h"

static int	handle_input_redirection(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
		return (handle_file_error(redir->file));
	if (dup2(fd, STDIN_FILENO) == -1)
		return (handle_dup2_error(fd));
	close(fd);
	return (0);
}

static int	handle_output_redirection(t_redir *redir, t_redir_type type)
{
	int	fd;

	if (type == REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (handle_file_error(redir->file));
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (handle_dup2_error(fd));
	close(fd);
	return (0);
}

int	setup_redirections(t_cmd *cmd)
{
	t_redir	*redir;
	int		status;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			if (handle_input_redirection(redir) != 0)
				return (1);
		}
		else if (redir->type == REDIR_OUT
			|| redir->type == REDIR_APPEND)
		{
			if (handle_output_redirection(redir, redir->type) != 0)
				return (1);
		}
		else if (redir->type == REDIR_HEREDOC)
		{
			status = handle_heredoc_redirection(redir);
			if (status != 0)
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
