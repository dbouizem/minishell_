/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_wait.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:55:48 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/30 13:02:06 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	wait_child_process(pid_t pid, int *status)
{
	int	ret;

	ret = waitpid(pid, status, 0);
	while (ret == -1 && errno == EINTR)
		ret = waitpid(pid, status, 0);
	return (ret);
}

static int	update_wait_status(int status, t_shell *shell, int *printed,
				int *sigint_seen)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (sigint_seen && WTERMSIG(status) == SIGINT)
			*sigint_seen = 1;
		report_signal_status(WTERMSIG(status), status, shell, printed);
		return (128 + WTERMSIG(status));
	}
	return (1);
}

static int	wait_children_loop(pid_t *pids, int num_commands, t_shell *shell)
{
	int	i;
	int	status;
	int	last_status;
	int	printed[2];
	int	sigint_seen;

	last_status = 0;
	sigint_seen = 0;
	ft_bzero(printed, sizeof(printed));
	i = 0;
	while (i < num_commands)
	{
		if (pids[i] > 0)
		{
			if (wait_child_process(pids[i], &status) == -1)
				last_status = 1;
			else
				last_status = update_wait_status(status, shell,
						printed, &sigint_seen);
		}
		i++;
	}
	if (sigint_seen)
		return (130);
	return (last_status);
}

int	wait_all_children(pid_t *pids, int num_commands, t_shell *shell)
{
	struct sigaction	sa;
	struct sigaction	old_int;
	struct sigaction	old_quit;
	int					last_status;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, &old_int);
	sigaction(SIGQUIT, &sa, &old_quit);
	last_status = wait_children_loop(pids, num_commands, shell);
	sigaction(SIGINT, &old_int, NULL);
	sigaction(SIGQUIT, &old_quit, NULL);
	return (last_status);
}
