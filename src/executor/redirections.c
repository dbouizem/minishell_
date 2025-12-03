#include "../includes/minishell.h"

int	setup_redirections(t_cmd *cmd)
{
	t_redir	*redir;
	int		fd;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == INPUT) // <
		{
			fd = open(redir->file, O_RDONLY);
			if (fd == -1 || dup2(fd, STDIN_FILENO) == -1)
			{
				if (fd != -1)
					close(fd);
				perror(redir->file);
				return (1);
			}
			close(fd);
		}
		else if (redir->type == TRUNC) // >
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1)
			{
				if (fd != -1)
					close(fd);
				perror(redir->file);
				return (1);
			}
			close(fd);
		}
		else if (redir->type == APPEND) // >>
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1)
			{
				if (fd != -1)
					close(fd);
				perror(redir->file);
				return (1);
			}
			close(fd);
		}
		else if (redir->type == HEREDOC) // <<
		{
			fd = open(redir->file, O_RDONLY);
			if (fd == -1 || dup2(fd, STDIN_FILENO) == -1)
			{
				if (fd != -1)
					close(fd);
				perror(redir->file);
				return (1);
			}
			close(fd);
		}
		redir = redir->next;
	}
	return (0);
}
