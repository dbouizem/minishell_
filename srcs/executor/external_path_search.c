#include "../../includes/minishell.h"

static char	*build_full_path(t_path_search *search, size_t start,
		size_t len)
{
	char	*dir;
	char	*full_path;

	if (len == 0)
		dir = ft_strdup(".");
	else
		dir = ft_substr(search->path, start, len);
	if (!dir)
		return (NULL);
	full_path = ft_strjoin3(dir, "/", search->cmd);
	free(dir);
	return (full_path);
}

static char	*check_path_entry(t_path_search *search, size_t start,
		size_t len)
{
	struct stat	st;
	char		*full_path;

	full_path = build_full_path(search, start, len);
	if (!full_path)
		return (NULL);
	if (access(full_path, F_OK) != 0)
		return (free(full_path), NULL);
	if (stat(full_path, &st) == 0 && S_ISDIR(st.st_mode))
		return (free(full_path), NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	if (search->path_error && *search->path_error == PATH_ERR_NONE)
		*search->path_error = PATH_ERR_PERM;
	return (free(full_path), NULL);
}

static char	*search_paths_loop(t_path_search *search)
{
	size_t		i;
	size_t		start;
	char		*full_path;
	const char	*path;

	path = search->path;
	i = 0;
	start = 0;
	while (1)
	{
		if (path[i] == ':' || path[i] == '\0')
		{
			full_path = check_path_entry(search, start, i - start);
			if (full_path)
				return (full_path);
			if (path[i] == '\0')
				break ;
			start = i + 1;
		}
		i++;
	}
	return (NULL);
}

char	*search_in_paths(const char *path, char *cmd, int *path_error)
{
	t_path_search	search;

	if (!path)
		return (NULL);
	search.path = path;
	search.cmd = cmd;
	search.path_error = path_error;
	return (search_paths_loop(&search));
}

char	*handle_absolute_path(char *cmd)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) == -1)
		return (NULL);
	if (S_ISDIR(path_stat.st_mode))
		return (NULL);
	if (access(cmd, X_OK) != 0)
		return (NULL);
	return (ft_strdup(cmd));
}
