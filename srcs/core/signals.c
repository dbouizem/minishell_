/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:40:00 by dbouizem          #+#    #+#             */
/*   Updated: 2025/12/08 18:40:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#ifndef ECHOCTL
# define ECHOCTL 0
#endif

static int	is_echoctl_enabled(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return (0);
	return ((term.c_lflag & ECHO) && (term.c_lflag & ECHOCTL));
}

static int	readline_getc(FILE *stream)
{
	unsigned char	c;
	ssize_t			nread;

	while (1)
	{
		nread = read(fileno(stream), &c, 1);
		if (nread == 1)
			return (c);
		if (nread == 0)
			return (EOF);
		if (errno == EINTR)
		{
			if (g_signal == SIGINT || g_signal == SIGQUIT)
				return ('\n');
			continue ;
		}
		return (EOF);
	}
}

static void	handle_prompt_signal(int signo)
{
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return ;
	if (signo == SIGQUIT && (!rl_line_buffer || !rl_line_buffer[0]))
		return ;
	g_signal = signo;
	if (signo == SIGINT)
	{
		rl_done = 1;
		if (!is_echoctl_enabled())
			write(STDOUT_FILENO, "^C\n", 3);
		else
			write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	rl_done = 1;
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	if (isatty(STDIN_FILENO))
		rl_getc_function = readline_getc;
	sa_int.sa_handler = handle_prompt_signal;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = handle_prompt_signal;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
