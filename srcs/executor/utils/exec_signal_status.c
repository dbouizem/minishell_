/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signal_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:56:05 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/28 16:56:06 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

#ifdef WCOREDUMP

static void	print_sigquit_message(int status, int echoctl)
{
	if (!echoctl)
		ft_putstr_fd("^\\", STDERR_FILENO);
	if (WCOREDUMP(status))
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	else
		ft_putstr_fd("Quit\n", STDERR_FILENO);
}

#else

static void	print_sigquit_message(int status, int echoctl)
{
	(void)status;
	if (!echoctl)
		ft_putstr_fd("^\\", STDERR_FILENO);
	ft_putstr_fd("Quit\n", STDERR_FILENO);
}

#endif

void	report_signal_status(int sig, int status, t_shell *shell,
			int *printed)
{
	int	echoctl;

	if (!shell || !shell->interactive)
		return ;
	echoctl = is_echoctl_enabled();
	if (sig == SIGINT && (!printed || !printed[0]))
	{
		if (echoctl)
			ft_putstr_fd("\n", STDERR_FILENO);
		else
			ft_putstr_fd("^C\n", STDERR_FILENO);
		if (printed)
			printed[0] = 1;
	}
	else if (sig == SIGQUIT && (!printed || !printed[1]))
	{
		print_sigquit_message(status, echoctl);
		if (printed)
			printed[1] = 1;
	}
}
