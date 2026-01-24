/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:40:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/24 08:26:26 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_echoctl_enabled(void)
{
#ifdef ECHOCTL

	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return (0);
	return ((term.c_lflag & ECHO) && (term.c_lflag & ECHOCTL));
	
#else
	return (0);
#endif
}

static int	readline_getc(FILE *stream)
{
	unsigned char	c;
	ssize_t			nread;

	(void)stream;
	while (1)
	{
		nread = read(STDIN_FILENO, &c, 1);
		if (nread == 1)
			return (c);
		if (nread == 0)
			return (EOF);
		if (errno != EINTR)
			return (EOF);
		if (g_signal == SIGINT || g_signal == SIGQUIT)
			return ('\n');
	}
}

static void	handle_prompt_signal(int signo)
{
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return ;
	if (signo == SIGQUIT)
		return ;
	g_signal = signo;
	if (signo == SIGINT)
	{
		if (!is_echoctl_enabled())
			write(STDOUT_FILENO, "^C", 2);
	}
	rl_done = 1;
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
