/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:40:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/24 10:02:13 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	trim_trailing_newline(char *line)
{
	size_t	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static char	*read_heredoc_basic(int show_prompt)
{
	char	*line;

	if (show_prompt)
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
	line = ft_gnl(STDIN_FILENO);
	if (!line)
		return (NULL);
	trim_trailing_newline(line);
	return (line);
}

static char	*read_heredoc_readline(void)
{
	return (readline("heredoc> "));
}

char	*read_heredoc_line(t_shell *shell)
{
	if (!shell || !shell->interactive)
		return (read_heredoc_basic(0));
	return (read_heredoc_readline());
}
