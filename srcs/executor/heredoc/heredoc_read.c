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

#ifndef ECHOCTL
# define ECHOCTL 0
#endif

static void	trim_trailing_newline(char *line)
{
	size_t	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static void	disable_echoctl(struct termios *orig_term, int *restore_term)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, orig_term) == 0)
	{
		term = *orig_term;
		term.c_lflag &= ~ECHOCTL;
		if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == 0)
			*restore_term = 1;
	}
}

static void	restore_echoctl(struct termios *orig_term, int restore_term)
{
	if (restore_term)
		tcsetattr(STDIN_FILENO, TCSANOW, orig_term);
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

char	*read_heredoc_line(t_shell *shell)
{
	char			*line;
	struct termios	orig_term;
	int				restore_term;

	if (!shell || !shell->interactive)
		return (read_heredoc_basic(0));
	restore_term = 0;
	disable_echoctl(&orig_term, &restore_term);
	line = read_heredoc_basic(1);
	restore_echoctl(&orig_term, restore_term);
	return (line);
}
