#include "../../../includes/minishell.h"

static int	build_heredoc_path(char *path, size_t size, int counter)
{
	char	*num;

	num = ft_itoa(counter);
	if (!num)
	{
		errno = ENOMEM;
		return (0);
	}
	ft_strlcpy(path, "/tmp/.minishell_heredoc_", size);
	ft_strlcat(path, num, size);
	free(num);
	return (1);
}

int	open_heredoc_tmp(char *path, size_t size)
{
	static int	counter;
	int			fd;
	int			attempts;

	attempts = 0;
	while (attempts < 10000)
	{
		if (!build_heredoc_path(path, size, counter++))
			return (-1);
		fd = open(path, O_CREAT | O_EXCL | O_WRONLY, 0600);
		if (fd >= 0)
			return (fd);
		if (errno != EEXIST)
			return (-1);
		attempts++;
	}
	errno = EEXIST;
	return (-1);
}

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
