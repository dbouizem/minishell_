#include "../../includes/minishell.h"

int	count_commands(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

int	**cleanup_partial_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pipes[i])
		{
			if (pipes[i][0] >= 0)
				close(pipes[i][0]);
			if (pipes[i][1] >= 0)
				close(pipes[i][1]);
			free(pipes[i]);
		}
		i++;
	}
	free(pipes);
	return (NULL);
}

int	fork_all_commands(t_pipeline_data *data)
{
	int		i;
	t_cmd	*current_cmd;

	i = 0;
	current_cmd = data->cmd;
	while (i < data->num_pipes + 1 && current_cmd)
	{
		data->pids[i] = fork();
		if (data->pids[i] == 0)
		{
			setup_child_signals();
			setup_child_pipes(data->pipes, i, data->num_pipes);
			cleanup_child_pipes(data->pipes, data->num_pipes, i);
			execute_command_child(current_cmd, data->shell);
			exit(1);
		}
		else if (data->pids[i] > 0)
			current_cmd = current_cmd->next;
		else
		{
			perror("minishell: fork");
			break ;
		}
		i++;
	}
	return (i);
}

void	close_all_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
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
	return (0);
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

static void	report_signal_status(int sig, int status, t_shell *shell,
		int *printed_int, int *printed_quit)
{
	int	echoctl;

	if (!shell || !shell->interactive)
		return ;
	echoctl = is_echoctl_enabled();
	if (sig == SIGINT && !(*printed_int))
	{
		print_sigint_message(echoctl);
		*printed_int = 1;
	}
	else if (sig == SIGQUIT && !(*printed_quit))
	{
		print_sigquit_message(status, echoctl);
		*printed_quit = 1;
	}
}

static int	update_wait_status(int status, t_shell *shell,
		int *printed_int, int *printed_quit)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		report_signal_status(WTERMSIG(status), status, shell,
			printed_int, printed_quit);
		return (128 + WTERMSIG(status));
	}
	return (1);
}

static int	wait_children_loop(pid_t *pids, int num_commands, t_shell *shell)
{
	int	i;
	int	status;
	int	last_status;
	int	ret;
	int	printed_int;
	int	printed_quit;

	i = 0;
	last_status = 0;
	printed_int = 0;
	printed_quit = 0;
	while (i < num_commands)
	{
		if (pids[i] <= 0)
		{
			i++;
			continue ;
		}
		ret = wait_child_process(pids[i], &status);
		if (ret == -1)
			last_status = 1;
		else
			last_status = update_wait_status(status, shell,
					&printed_int, &printed_quit);
		i++;
	}
	return (last_status);
}

int	wait_all_children(pid_t *pids, int num_commands, t_shell *shell)
{
	int					last_status;
	struct sigaction	old_int;
	struct sigaction	old_quit;

	set_wait_signals(&old_int, &old_quit);
	last_status = wait_children_loop(pids, num_commands, shell);
	restore_wait_signals(&old_int, &old_quit);
	return (last_status);
}
