#include "../includes/minishell.h"

static int	write_heredoc_content(int fd, char *delimiter)
{
	char	*line;
	char	*delim_cpy;

	delim_cpy = remove_quotes(delimiter);
	if (!delim_cpy)
		return (1);
	while (1)
	{
		if (g_signal == 1)
			return (free(delim_cpy), 130);
		line = readline("heredoc> ");
		if (g_signal == 1)
			return (free(line), free(delim_cpy), 130);
		if (!line)
		{
			ft_putstr_fd("minishell: warning: heredoc delimited by ", 2);
			ft_putstr_fd("EOF (wanted `", 2);
			ft_putstr_fd(delimiter, 2);
			ft_putstr_fd("')\n", 2);
			return (free(delim_cpy), 0);
		}
		if (ft_strcmp(line, delim_cpy) == 0)
			return (free(line), free(delim_cpy), 0);
		if (write(fd, line, ft_strlen(line)) == -1
			|| write(fd, "\n", 1) == -1)
		{
			free(line);
			free(delim_cpy);
			return (perror("minishell: heredoc"), 1);
		}
		free(line);
	}
}

int	handle_heredoc_redirection(t_redir *redir)
{
	char				*tmp_filename;
	int					fd;
	int					status;
	struct sigaction	old_int;
	struct sigaction	old_quit;

	tmp_filename = "/tmp/minishell_heredocXXXXXX";
	fd = mkstemp(tmp_filename);
	if (fd == -1)
		return (handle_file_error("heredoc"));
	g_signal = 0;
	setup_heredoc_signals(&old_int, &old_quit);
	status = write_heredoc_content(fd, redir->file);
	restore_signals(&old_int, &old_quit);
	if (status == 130)
		return (close(fd), unlink(tmp_filename), 130);
	if (status != 0)
		return (close(fd), unlink(tmp_filename), 1);
	if (lseek(fd, 0, SEEK_SET) == -1)
		return (perror("minishell: heredoc"), close(fd), unlink(tmp_filename), 1);
	unlink(tmp_filename);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (handle_dup2_error(fd));
	close(fd);
	return (0);
}
