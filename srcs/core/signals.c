#include "../../includes/minishell.h"

#ifdef ECHOCTL

static int	is_echoctl_enabled(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return (0);
	return ((term.c_lflag & ECHO) && (term.c_lflag & ECHOCTL));
}
#else

static int	is_echoctl_enabled(void)
{
	return (0);
}

#endif

void	handle_sigint(int signo)
{
	g_signal = signo;
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return ;
	rl_done = 1;
	if (!is_echoctl_enabled())
		write(STDOUT_FILENO, "^C\n", 3);
	else
		write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
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

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
