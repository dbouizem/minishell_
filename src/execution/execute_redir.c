#include "../includes/minishell.h"

//Pour heredoc, le delimiteur est redir->file


int	apply_single_redir(t_redir *redir)
{
	int fd;

	fd = open(redir->file, O_RDWR | O_CREAT);
	if (fd < 0)
		return (1);
	if (redir->type == HEREDOC)
	{
		printf("%s\n", redir->file);
		printf("%d\n", redir->type);
	}
	else
		return (1);
	close(fd);
	return (0);
}