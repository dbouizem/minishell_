#include "../../includes/minishell.h"

void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

pid_t	fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	return (pid);
}

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

static int	is_echoctl_enabled(void)
{
	int	echoctl;

	echoctl = 0;
#ifdef ECHOCTL
	{
		struct termios	term;

		if (tcgetattr(STDIN_FILENO, &term) == 0)
			echoctl = ((term.c_lflag & ECHOCTL) != 0);
	}
#endif
	return (echoctl);
}

static void	print_sigint_message(int echoctl)
{
	if (echoctl)
		ft_putstr_fd("\n", STDERR_FILENO);
	else
		ft_putstr_fd("^C\n", STDERR_FILENO);
}

static void	print_sigquit_message(int status, int echoctl)
{
	if (!echoctl)
		ft_putstr_fd("^\\", STDERR_FILENO);
#ifdef WCOREDUMP
	if (WCOREDUMP(status))
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	else
		ft_putstr_fd("Quit\n", STDERR_FILENO);
#else
	ft_putstr_fd("Quit\n", STDERR_FILENO);
#endif
}

static void	report_signal_status(int sig, int status, t_shell *shell)
{
	int	echoctl;

	if (!shell || !shell->interactive)
		return ;
	echoctl = is_echoctl_enabled();
	if (sig == SIGINT)
		print_sigint_message(echoctl);
	else if (sig == SIGQUIT)
		print_sigquit_message(status, echoctl);
}

static void	update_exit_status(int status, t_shell *shell)
{
	if (!shell)
		return ;
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		report_signal_status(WTERMSIG(status), status, shell);
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

void	handle_execve_error(char *cmd_path)
{
	int	err;

	err = errno;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd_path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(err), STDERR_FILENO);
	free(cmd_path);
	if (err == ENOENT)
		exit(127);
	exit(126);
}

int	handle_pipe_error(void)
{
	perror("pipe");
	return (1);
}
