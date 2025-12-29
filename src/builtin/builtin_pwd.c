#include "../../includes/minishell.h"

static char	*getcwd_dynamic(void)
{
	size_t	size;
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf)
		return (buf);
	size = 128;
	buf = malloc(size);
	if (!buf)
		return (NULL);
	while (!getcwd(buf, size))
	{
		if (errno != ERANGE)
		{
			free(buf);
			return (NULL);
		}
		free(buf);
		size *= 2;
		buf = malloc(size);
		if (!buf)
			return (NULL);
	}
	return (buf);
}

int	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd_dynamic();
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
		return (0);
	}
	else
	{
		perror("minishell: pwd");
		return (1);
	}
}
