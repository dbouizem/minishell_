/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:56:00 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/28 16:56:01 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
	perror("minishell: dup2");
	if (fd != -1)
		close(fd);
	return (1);
}

int	handle_malloc_error(void)
{
	perror("malloc");
	return (1);
}

int	handle_input_redirection(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
		return (handle_file_error(redir->file));
	if (dup2(fd, STDIN_FILENO) == -1)
		return (handle_dup2_error(fd));
	close(fd);
	return (0);
}

int	handle_output_redirection(t_redir *redir, t_redir_type type)
{
	int	fd;

	if (type == REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (handle_file_error(redir->file));
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (handle_dup2_error(fd));
	close(fd);
	return (0);
}
