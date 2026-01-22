#include "../../../includes/minishell.h"

static char	*read_heredoc_basic(int show_prompt)
{
	char	*line;
	size_t	len;

	if (show_prompt)
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
	line = ft_gnl(STDIN_FILENO);
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

char	*read_heredoc_line(t_shell *shell)
{
	char			*line;
	size_t			len;

	if (!shell || !shell->interactive)
		return (read_heredoc_basic(0));
	line = read_heredoc_basic(1);
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}
