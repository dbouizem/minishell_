#include "../../includes/minishell.h"

static void	set_wait_signals(struct sigaction *old_int,
		struct sigaction *old_quit)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, old_int);
	sigaction(SIGQUIT, &sa, old_quit);
}

static void	restore_wait_signals(struct sigaction *old_int,
		struct sigaction *old_quit)
{
	sigaction(SIGINT, old_int, NULL);
	sigaction(SIGQUIT, old_quit, NULL);
}

static int	wait_child_process(pid_t pid, int *status)
{
	int	ret;

	ret = waitpid(pid, status, 0);
	while (ret == -1 && errno == EINTR)
		ret = waitpid(pid, status, 0);
	return (ret);
}

static void	update_exit_status(int status, t_shell *shell)
{
	if (!shell)
		return ;
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		report_signal_status(WTERMSIG(status), status, shell, NULL);
		shell->exit_status = 128 + WTERMSIG(status);
	}
	else
		shell->exit_status = 1;
}

void	wait_for_child(pid_t pid, int *status, t_shell *shell)
{
	int					ret;
	struct sigaction	old_int;
	struct sigaction	old_quit;

	if (!status)
		return ;
	set_wait_signals(&old_int, &old_quit);
	ret = wait_child_process(pid, status);
	restore_wait_signals(&old_int, &old_quit);
	if (ret == -1)
	{
		perror("waitpid");
		if (shell)
			shell->exit_status = 1;
		return ;
	}
	update_exit_status(*status, shell);
}
