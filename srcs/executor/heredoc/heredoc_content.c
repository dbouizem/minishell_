/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:55:27 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/28 16:55:28 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	heredoc_warn_eof(char *delimiter)
{
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		write(STDERR_FILENO, "\n", 1);
	ft_putstr_fd("minishell: warning: here-document delimited by ", 2);
	ft_putstr_fd("end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
	return (0);
}

static int	write_heredoc_line(t_heredoc_params *params, char *line)
{
	char	*expanded;

	expanded = line;
	if (params->expand)
	{
		expanded = expand_heredoc_line(line, params->shell);
		if (!expanded)
			return (1);
	}
	if (write(params->fd, expanded, ft_strlen(expanded)) == -1
		|| write(params->fd, "\n", 1) == -1)
	{
		if (params->expand)
			free(expanded);
		perror("minishell: heredoc");
		return (1);
	}
	if (params->expand)
		free(expanded);
	return (2);
}

static int	handle_heredoc_line(t_heredoc_params *params, char *line,
		char *delim_cpy)
{
	if (!line)
		return (heredoc_warn_eof(params->delimiter));
	if (ft_strcmp(line, delim_cpy) == 0)
		return (0);
	return (write_heredoc_line(params, line));
}

static int	read_heredoc_status(t_heredoc_params *params, char *delim_cpy)
{
	char	*line;
	int		status;

	line = read_heredoc_line(params->shell);
	if (g_signal == SIGINT)
	{
		free(line);
		return (130);
	}
	status = handle_heredoc_line(params, line, delim_cpy);
	free(line);
	return (status);
}

int	write_heredoc_content(t_heredoc_params *params)
{
	char	*delim_cpy;
	int		status;

	delim_cpy = remove_heredoc_delimiter(params->delimiter);
	if (!delim_cpy)
		return (1);
	status = 2;
	while (status == 2)
	{
		if (g_signal == SIGINT)
			status = 130;
		else
			status = read_heredoc_status(params, delim_cpy);
	}
	free(delim_cpy);
	return (status);
}
