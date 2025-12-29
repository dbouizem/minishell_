#include "../../includes/minishell.h"

static int	is_heredoc_quoted(const char *delimiter)
{
	int	i;

	if (!delimiter)
		return (0);
	i = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == '\'' || delimiter[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

static int	append_part(char **result, char *part)
{
	char	*new_result;

	if (!part)
		return (free(*result), 0);
	new_result = ft_strjoin_free(*result, part);
	free(part);
	if (!new_result)
		return (0);
	*result = new_result;
	return (1);
}

static char	*append_char(char *line, size_t *len, size_t *cap, char c)
{
	size_t	new_cap;
	char	*new_line;

	if (*len + 2 > *cap)
	{
		new_cap = *cap * 2;
		if (new_cap < 64)
			new_cap = 64;
		while (new_cap < *len + 2)
			new_cap *= 2;
		new_line = malloc(new_cap);
		if (!new_line)
			return (free(line), NULL);
		if (line)
			ft_memcpy(new_line, line, *len);
		free(line);
		line = new_line;
		*cap = new_cap;
	}
	line[*len] = c;
	(*len)++;
	return (line);
}

static int	setup_heredoc_term(t_shell *shell, struct termios *saved)
{
	struct termios	term;

	if (!shell || !shell->interactive)
		return (0);
	if (tcgetattr(STDIN_FILENO, saved) == -1)
		return (0);
	term = *saved;
	term.c_lflag |= ISIG;
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
#ifdef ECHOCTL
	term.c_lflag &= ~ECHOCTL;
#endif
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		return (0);
	return (1);
}

static void	restore_heredoc_term(t_shell *shell, struct termios *saved)
{
	if (!shell || !shell->interactive)
		return ;
	tcsetattr(STDIN_FILENO, TCSANOW, saved);
}

static char	*read_heredoc_line(t_shell *shell, int manual_echo)
{
	char	*line;
	size_t	len;
	size_t	cap;
	char	ch;
	ssize_t	n;
	int		interactive;

	interactive = (shell && shell->interactive);
	if (interactive)
		write(STDOUT_FILENO, "heredoc> ", 9);
	line = NULL;
	len = 0;
	cap = 0;
	while (1)
	{
		n = read(STDIN_FILENO, &ch, 1);
		if (n == -1)
			return (free(line), NULL);
		if (n == 0)
			break ;
		if (ch == '\x03')
		{
			g_signal = SIGINT;
			if (interactive)
				write(STDOUT_FILENO, "^C\n", 3);
			return (free(line), NULL);
		}
		if (ch == '\x04')
		{
			if (len == 0)
			{
				if (interactive)
					write(STDOUT_FILENO, "\n", 1);
				return (free(line), NULL);
			}
			break ;
		}
		if (ch == '\n')
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break ;
		}
		if (ch == '\b' || ch == 127)
		{
			if (len > 0)
			{
				len--;
				if (interactive && manual_echo)
					write(STDOUT_FILENO, "\b \b", 3);
			}
			continue ;
		}
		line = append_char(line, &len, &cap, ch);
		if (!line)
			return (NULL);
		if (interactive && manual_echo)
			write(STDOUT_FILENO, &ch, 1);
	}
	if (n == 0 && len == 0)
		return (free(line), NULL);
	if (!line)
		return (ft_strdup(""));
	line[len] = '\0';
	return (line);
}

static char	*expand_heredoc_line(char *line, t_shell *shell)
{
	char	*result;
	char	*part;
	int		i;

	if (!line)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			part = process_dollar(line, &i, shell);
		else
			part = char_to_str(line[i++]);
		if (!append_part(&result, part))
			return (NULL);
	}
	return (result);
}

static int	handle_heredoc_line(int fd, char *line, char *delim_cpy,
		char *delimiter, int expand, t_shell *shell)
{
	char	*expanded;

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
	expanded = line;
	if (expand)
	{
		expanded = expand_heredoc_line(line, shell);
		if (!expanded)
			return (1);
	}
	if (write(fd, expanded, ft_strlen(expanded)) == -1
		|| write(fd, "\n", 1) == -1)
	{
		if (expand)
			free(expanded);
		perror("minishell: heredoc");
		return (1);
	}
	if (expand)
		free(expanded);
	return (2);
}

static int	read_heredoc_status(int fd, char *delim_cpy, char *delimiter,
		int expand, t_shell *shell, int manual_echo)
{
	char	*line;
	int		status;

	line = read_heredoc_line(shell, manual_echo);
	if (g_signal == SIGINT)
	{
		free(line);
		return (130);
	}
	status = handle_heredoc_line(fd, line, delim_cpy, delimiter,
			expand, shell);
	free(line);
	return (status);
}

static int	write_heredoc_content(int fd, char *delimiter, int expand,
		t_shell *shell, int manual_echo)
{
	char	*delim_cpy;
	int		status;

	delim_cpy = remove_quote(delimiter);
	if (!delim_cpy)
		return (1);
	status = 2;
	while (status == 2)
	{
		if (g_signal == SIGINT)
			status = 130;
		else
		{
			status = read_heredoc_status(fd, delim_cpy, delimiter,
					expand, shell, manual_echo);
		}
	}
	free(delim_cpy);
	return (status);
}

static int	finalize_heredoc_fd(int fd, char *tmp_filename, t_redir *redir)
{
	if (lseek(fd, 0, SEEK_SET) == -1)
	{
		perror("minishell: heredoc");
		close(fd);
		unlink(tmp_filename);
		return (1);
	}
	unlink(tmp_filename);
	redir->fd = fd;
	return (0);
}

int	handle_heredoc_redirection(t_redir *redir, t_shell *shell)
{
	char				tmp_filename[29];
	int					fd;
	int					status;
	struct sigaction	old_int;
	struct sigaction	old_quit;
	struct termios		saved_term;
	int					term_changed;
	int					expand;

	ft_strlcpy(tmp_filename, "/tmp/heredocXXXXXX", 29);
	fd = mkstemp(tmp_filename);
	if (fd == -1)
		return (handle_file_error("heredoc"));
	if (redir->fd != -1)
	{
		close(redir->fd);
		redir->fd = -1;
	}
	g_signal = 0;
	expand = !is_heredoc_quoted(redir->file);
	term_changed = setup_heredoc_term(shell, &saved_term);
	setup_heredoc_signals(&old_int, &old_quit);
	status = write_heredoc_content(fd, redir->file, expand, shell,
			term_changed);
	restore_signals(&old_int, &old_quit);
	if (term_changed)
		restore_heredoc_term(shell, &saved_term);
	if (status != 0)
	{
		close(fd);
		unlink(tmp_filename);
		return (status);
	}
	return (finalize_heredoc_fd(fd, tmp_filename, redir));
}
