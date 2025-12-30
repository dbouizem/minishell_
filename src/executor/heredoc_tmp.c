#include "../../includes/minishell.h"

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

int	setup_heredoc_term(t_shell *shell, struct termios *saved)
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
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		return (0);
	return (1);
}

void	restore_heredoc_term(t_shell *shell, struct termios *saved)
{
	if (!shell || !shell->interactive)
		return ;
	tcsetattr(STDIN_FILENO, TCSANOW, saved);
}
