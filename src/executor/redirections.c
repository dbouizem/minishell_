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

static int	handle_output_redirection(t_redir *redir, int type)
{
	int	fd;

	if (type == TRUNC)
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

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == INPUT)
		{
			if (handle_input_redirection(redir) != 0)
				return (1);
		}
		else if (redir->type == TRUNC || redir->type == APPEND)
		{
			if (handle_output_redirection(redir, redir->type) != 0)
				return (1);
		}
		else if (redir->type == HEREDOC)
		{
			if (handle_heredoc_redirection(redir) != 0)
				return (1);
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
