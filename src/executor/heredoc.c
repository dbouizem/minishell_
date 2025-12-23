#include "../../includes/minishell.h"

static int	handle_heredoc_line(int fd, char *line, char *delim_cpy,
		char *delimiter)
{
	if (!line)
	{
		ft_putstr_fd("minishell: warning: heredoc delimited by ", 2);
		ft_putstr_fd("EOF (wanted `", 2);
		ft_putstr_fd(delimiter, 2);
		ft_putstr_fd("')\n", 2);
		return (0);
	}
	if (ft_strcmp(line, delim_cpy) == 0)
		return (0);
	if (write(fd, line, ft_strlen(line)) == -1
		|| write(fd, "\n", 1) == -1)
	{
		perror("minishell: heredoc");
		return (1);
	}
	return (2);
}

static int	read_heredoc_status(int fd, char *delim_cpy, char *delimiter)
{
	char	*line;
	int		status;

	line = readline("heredoc> ");
	if (g_signal == 1)
	{
		free(line);
		return (130);
	}
	status = handle_heredoc_line(fd, line, delim_cpy, delimiter);
	free(line);
	return (status);
}

static int	write_heredoc_content(int fd, char *delimiter)
{
	char	*delim_cpy;
	int		status;

	delim_cpy = remove_quote(delimiter);
	if (!delim_cpy)
		return (1);
	status = 2;
	while (status == 2)
	{
		if (g_signal == 1)
			status = 130;
		else
		{
			status = read_heredoc_status(fd, delim_cpy, delimiter);
		}
	}
	free(delim_cpy);
	return (status);
}

static int	finalize_heredoc_fd(int fd, char *tmp_filename)
{
	if (lseek(fd, 0, SEEK_SET) == -1)
	{
		perror("minishell: heredoc");
		close(fd);
		unlink(tmp_filename);
		return (1);
	}
	unlink(tmp_filename);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (handle_dup2_error(fd));
	close(fd);
	return (0);
}

int	handle_heredoc_redirection(t_redir *redir)
{
	char				tmp_filename[29];
	int					fd;
	int					status;
	struct sigaction	old_int;
	struct sigaction	old_quit;

	ft_strlcpy(tmp_filename, "/tmp/heredocXXXXXX", 29);
	fd = mkstemp(tmp_filename);
	if (fd == -1)
		return (handle_file_error("heredoc"));
	g_signal = 0;
	setup_heredoc_signals(&old_int, &old_quit);
	status = write_heredoc_content(fd, redir->file);
	restore_signals(&old_int, &old_quit);
	if (status != 0)
	{
		close(fd);
		unlink(tmp_filename);
		return (status);
	}
	return (finalize_heredoc_fd(fd, tmp_filename));
}
