#include "../includes/minishell.h"

static void restore_signals(struct sigaction *old_int,
		struct sigaction *old_quit)
{
	sigaction(SIGINT, old_int, NULL);
	sigaction(SIGQUIT, old_quit, NULL);
}

static void heredoc_sigint_handler(int signo)
{
	(void)signo;
	g_signal = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_done = 1;
}

static void setup_heredoc_signals(struct sigaction *old_int,
		struct sigaction *old_quit)
{
	struct sigaction sa;

	sa.sa_handler = heredoc_sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, old_int);

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, old_quit);
}

static int write_heredoc_content(int fd, char *delimiter)
{
	char *line;

	while (1)
	{
		if (g_signal == 1)
			return (130);
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: heredoc delimited by ", 2);
			ft_putstr_fd("EOF (wanted `", 2);
			ft_putstr_fd(delimiter, 2);
			ft_putstr_fd("')\n", 2);
			return (0);
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			return (0);
		}
		if (write(fd, line, ft_strlen(line)) == -1
			|| write(fd, "\n", 1) == -1)
		{
			free(line);
			perror("minishell: heredoc");
			return (1);
		}
		free(line);
	}
}

int	handle_heredoc_redirection(t_redir *redir)
{
	char tmp_filename[] = "/tmp/minishell_heredoc.txt";
	int	fd;
	int status;
	struct sigaction old_int;
	struct sigaction old_quit;

	fd = open(tmp_filename, O_CREAT | O_RDWR);
	if (fd == -1)
		return (handle_file_error("heredoc"));
	g_signal = 0;
	setup_heredoc_signals(&old_int, &old_quit);
	status = write_heredoc_content(fd, redir->file);
	restore_signals(&old_int, &old_quit);
	if (status == 130)
	{
		close(fd);
		unlink(tmp_filename);
		return (130);
	}
	if (status != 0)
	{
		close(fd);
		unlink(tmp_filename);
		return (1);
	}
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