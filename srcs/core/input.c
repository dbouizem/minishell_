#include "../../includes/minishell.h"

static int	can_use_readline(void)
{
	int	fd;

	fd = open("/dev/null", O_RDONLY);
	if (fd == -1)
	{
		if (errno == EMFILE || errno == ENFILE)
			return (0);
		return (1);
	}
	close(fd);
	return (1);
}

static char	*read_input_fallback(void)
{
	char	*line;
	size_t	len;

	ft_putstr_fd("minishell$ ", STDOUT_FILENO);
	line = ft_gnl(STDIN_FILENO);
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

char	*read_input(void)
{
	char	*input;

	if (!can_use_readline())
		return (perror("minishell: readline"), read_input_fallback());
	errno = 0;
	input = readline(PROMPT_COLOR "minishell$ " RESET_COLOR);
	if (!input)
	{
		if (errno == EINTR)
			return (NULL);
		if (errno == EMFILE || errno == ENFILE)
		{
			perror("minishell: readline");
			return (read_input_fallback());
		}
		if (errno)
			perror("minishell: readline error");
		return (NULL);
	}
	if (*input)
		add_history(input);
	rl_replace_line("", 0);
	rl_on_new_line();
	return (input);
}

char	*read_input_non_interactive(void)
{
	char	*line;
	size_t	len;

	line = ft_gnl(STDIN_FILENO);
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}
