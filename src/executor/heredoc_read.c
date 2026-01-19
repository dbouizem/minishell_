/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:05:00 by dbouizem          #+#    #+#             */
/*   Updated: 2025/12/08 19:05:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_backspace(char ch, t_heredoc_state *state)
{
	if (ch != '\b' && ch != 127)
		return (0);
	if (state->len > 0)
	{
		state->len--;
		if (state->interactive && state->manual_echo)
			write(STDOUT_FILENO, "\b \b", 3);
	}
	return (2);
}

static int	handle_control_char(char ch, t_heredoc_state *state)
{
	if (ch == '\x03')
	{
		g_signal = SIGINT;
		if (state->interactive)
			write(STDOUT_FILENO, "^C\n", 3);
		return (-1);
	}
	if (ch == '\x04')
	{
		if (state->len == 0 && state->interactive)
			write(STDOUT_FILENO, "\n", 1);
		if (state->len == 0)
			return (-1);
		return (1);
	}
	if (ch == '\n')
	{
		if (state->interactive)
			write(STDOUT_FILENO, "\n", 1);
		return (1);
	}
	return (handle_backspace(ch, state));
}

static int	process_heredoc_char(char ch, t_heredoc_state *state)
{
	int	action;

	action = handle_control_char(ch, state);
	if (action != 0)
		return (action);
	state->line = heredoc_append_char(state->line, &state->len,
			&state->cap, ch);
	if (!state->line)
		return (-1);
	if (state->interactive && state->manual_echo)
		write(STDOUT_FILENO, &ch, 1);
	return (0);
}

static char	*read_heredoc_loop(t_heredoc_state *state)
{
	char	ch;
	int		action;

	while (1)
	{
		state->last_read = read(STDIN_FILENO, &ch, 1);
		if (state->last_read <= 0)
			break ;
		action = process_heredoc_char(ch, state);
		if (action < 0)
			return (free(state->line), NULL);
		if (action == 1)
			break ;
	}
	if (state->last_read == -1)
		return (free(state->line), NULL);
	return (state->line);
}

char	*read_heredoc_line(t_shell *shell, int manual_echo)
{
	t_heredoc_state	state;
	char			*line;

	if (!shell || !shell->interactive)
	{
		line = ft_gnl(STDIN_FILENO);
		if (line && line[0] && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		return (line);
	}
	state.interactive = 1;
	state.manual_echo = manual_echo;
	state.len = 0;
	state.cap = 0;
	state.line = NULL;
	write(STDOUT_FILENO, "heredoc> ", 9);
	line = read_heredoc_loop(&state);
	if (!line)
		return (NULL);
	return (heredoc_finalize_line(line, state.len, state.last_read));
}
