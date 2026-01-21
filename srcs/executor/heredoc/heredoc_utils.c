#include "../../../includes/minishell.h"

#ifdef ECHOCTL

static int	read_echoctl_flag(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == 0)
		return ((term.c_lflag & ECHO) && (term.c_lflag & ECHOCTL));
	return (0);
}
#else

static int	read_echoctl_flag(void)
{
	return (0);
}
#endif

static int	g_heredoc_echoctl;

void	restore_signals(struct sigaction *old_int,
		struct sigaction *old_quit)
{
	sigaction(SIGINT, old_int, NULL);
	sigaction(SIGQUIT, old_quit, NULL);
}

void	heredoc_sigint_handler(int signo)
{
	(void)signo;
	g_signal = SIGINT;
	if (isatty(STDIN_FILENO))
	{
		if (!g_heredoc_echoctl)
			write(STDOUT_FILENO, "^C\n", 3);
		else
			write(STDOUT_FILENO, "\n", 1);
	}
}

void	setup_heredoc_signals(struct sigaction *old_int,
		struct sigaction *old_quit)
{
	struct sigaction	sa;

	g_heredoc_echoctl = read_echoctl_flag();
	sa.sa_handler = heredoc_sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, old_int);
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, old_quit);
}
