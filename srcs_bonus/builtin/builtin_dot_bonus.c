/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dot_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:44:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/30 16:44:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	dot_error(t_shell *shell, char *path, char *msg, int status)
{
	ft_putstr_fd("minishell: .: ", STDERR_FILENO);
	if (path)
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(msg, STDERR_FILENO);
	if (shell)
		shell->exit_status = status;
	return (status);
}

static int	open_dot_file(char *path, t_shell *shell)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (dot_error(shell, path, strerror(errno), 1));
	if (S_ISDIR(st.st_mode))
		return (dot_error(shell, path, "Is a directory", 126));
	if (access(path, R_OK) != 0)
		return (dot_error(shell, path, "Permission denied", 126));
	return (open(path, O_RDONLY));
}

int	builtin_dot(char **args, t_shell *shell)
{
	int		fd;
	char	*line;

	if (!args || !args[1])
		return (dot_error(shell, NULL, "filename required", 2));
	fd = open_dot_file(args[1], shell);
	if (fd < 0)
		return (shell->exit_status);
	line = ft_gnl(fd);
	while (line)
	{
		process_input(line, shell);
		free(line);
		line = ft_gnl(fd);
	}
	close(fd);
	return (shell->exit_status);
}
