#include "../../../includes/minishell.h"

void	reset_heredoc_fd(t_redir *redir)
{
	if (redir->fd != -1)
	{
		close(redir->fd);
		redir->fd = -1;
	}
}

int	abort_heredoc(int fd, char *tmp_filename, int status)
{
	close(fd);
	unlink(tmp_filename);
	return (status);
}

int	finalize_heredoc_fd(int fd, char *tmp_filename, t_redir *redir)
{
	int	read_fd;

	if (close(fd) == -1)
	{
		perror("minishell: heredoc");
		unlink(tmp_filename);
		return (1);
	}
	read_fd = open(tmp_filename, O_RDONLY);
	if (read_fd == -1)
	{
		handle_file_error(tmp_filename);
		unlink(tmp_filename);
		return (1);
	}
	unlink(tmp_filename);
	redir->fd = read_fd;
	return (0);
}
