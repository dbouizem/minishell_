#include "../../includes/minishell.h"

static char	*read_heredoc_fallback(void)
{
	char	*line;
	size_t	len;

	ft_putstr_fd("heredoc> ", STDOUT_FILENO);
	line = ft_gnl(STDIN_FILENO);
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

static char	*read_heredoc_interactive(void)
{
	char	*line;

	errno = 0;
	line = readline("heredoc> ");
	if (!line)
	{
		if (errno == EMFILE || errno == ENFILE)
		{
			perror("minishell: readline");
			return (read_heredoc_fallback());
		}
		if (errno)
			perror("minishell: readline error");
	}
	return (line);
}

char	*read_heredoc_line(t_shell *shell, int manual_echo)
{
	char			*line;
	size_t			len;

	(void)manual_echo;
	if (!shell || !shell->interactive)
	{
		line = ft_gnl(STDIN_FILENO);
		if (line && line[0] && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		return (line);
	}
	line = read_heredoc_interactive();
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}
