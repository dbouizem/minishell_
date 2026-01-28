/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:55:50 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/28 16:55:51 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	close_cmd_heredocs(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC && redir->fd != -1)
		{
			close(redir->fd);
			redir->fd = -1;
		}
		redir = redir->next;
	}
}

void	close_pipeline_heredocs(t_cmd *cmd)
{
	while (cmd)
	{
		close_cmd_heredocs(cmd);
		if (cmd->separator != PIPE)
			break ;
		cmd = cmd->next;
	}
}

static int	prepare_cmd_heredocs(t_cmd *cmd, t_shell *shell)
{
	t_redir	*redir;
	int		status;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC && redir->fd == -1)
		{
			status = handle_heredoc_redirection(redir, shell);
			if (status != 0)
				return (status);
		}
		redir = redir->next;
	}
	return (0);
}

int	prepare_pipeline_heredocs(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*start;
	int		status;

	start = cmd;
	while (cmd)
	{
		status = prepare_cmd_heredocs(cmd, shell);
		if (status != 0)
		{
			close_pipeline_heredocs(start);
			return (status);
		}
		if (cmd->separator != PIPE)
			break ;
		cmd = cmd->next;
	}
	return (0);
}
