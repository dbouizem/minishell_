#include "../../includes/minishell.h"

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
