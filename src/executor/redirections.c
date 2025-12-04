#include "../includes/minishell.h"

int	setup_redirections(t_cmd *cmd)
{
	t_redir *redir;
	int fd;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == INPUT)  // <
		{
			fd = open(redir->file, O_RDONLY);
			if (fd == -1)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(redir->file, STDERR_FILENO);
				ft_putstr_fd(": ", STDERR_FILENO);
				ft_putendl_fd(strerror(errno), STDERR_FILENO);
				return (1);
			}
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				perror("dup2");
				close(fd);
				return (1);
			}
			close(fd);
		}
		else if (redir->type == TRUNC)  // >
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(redir->file, STDERR_FILENO);
				ft_putstr_fd(": ", STDERR_FILENO);
				ft_putendl_fd(strerror(errno), STDERR_FILENO);
				return (1);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("dup2");
				close(fd);
				return (1);
			}
			close(fd);
		}
		else if (redir->type == APPEND)  // >>
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(redir->file, STDERR_FILENO);
				ft_putstr_fd(": ", STDERR_FILENO);
				ft_putendl_fd(strerror(errno), STDERR_FILENO);
				return (1);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("dup2");
				close(fd);
				return (1);
			}
			close(fd);
		}
		else if (redir->type == HEREDOC)  // <<
		{
			fd = open(redir->file, O_RDONLY);
			if (fd == -1)
			{
				perror("heredoc");
				return (1);
			}
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				perror("dup2");
				close(fd);
				return (1);
			}
			close(fd);
		}

		redir = redir->next;
	}

	return (0);
}

int	save_redirections(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);

	if (*saved_stdin == -1 || *saved_stdout == -1)
	{
		perror("minishell: dup");
		if (*saved_stdin != -1)
			close(*saved_stdin);
		if (*saved_stdout != -1)
			close(*saved_stdout);
		return (1);
	}
	return (0);
}

int	restore_redirections(int saved_stdin, int saved_stdout)
{
	int	ret;

	ret = 0;
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2 stdin");
		ret = 1;
	}
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2 stdout");
		ret = 1;
	}
	close(saved_stdin);
	close(saved_stdout);
	return (ret);
}
