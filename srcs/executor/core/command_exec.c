/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:55:15 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/29 01:09:01 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	handle_command_execution(t_cmd *cmd, t_shell *shell,
				int saved_in, int saved_out)
{
	int	exit_status;

	if (!cmd->args || !cmd->args[0])
		exit_status = 0;
	else if (is_builtin(cmd->args[0]))
		exit_status = execute_builtin(cmd, shell);
	else
		exit_status = execute_external(cmd, shell);
	shell->exit_status = exit_status;
	if (cmd->redirs)
		restore_redirections(saved_in, saved_out);
	return (exit_status);
}

static int	handle_redir_status(t_cmd *cmd, t_shell *shell,
				int saved[2], int status)
{
	if (status == 130)
	{
		shell->exit_status = 130;
		if (cmd->redirs)
			restore_redirections(saved[0], saved[1]);
		return (130);
	}
	if (status != 0)
	{
		shell->exit_status = 1;
		if (cmd->redirs)
			restore_redirections(saved[0], saved[1]);
		return (1);
	}
	return (0);
}

int	execute_command(t_cmd *cmd, t_shell *shell)
{
	int	saved[2];
	int	status;

	if (cmd->redirs != NULL
		&& save_redirections(&saved[0], &saved[1]) != 0)
	{
		shell->exit_status = 1;
		return (1);
	}
	status = setup_redirections(cmd, shell);
	if (handle_redir_status(cmd, shell, saved, status) != 0)
		return (shell->exit_status);
	return (handle_command_execution(cmd, shell, saved[0], saved[1]));
}
