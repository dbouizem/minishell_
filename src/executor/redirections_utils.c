 #include "../includes/minishell.h"

int	handle_file_error(char *filename)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (1);
}

int	handle_dup2_error(int fd)
{
	perror("dup2");
	if (fd != -1)
		close(fd);
	return (1);
}

int	handle_malloc_error(void)
{
	perror("malloc");
	return (1);
}
