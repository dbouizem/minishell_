/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:56:31 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/28 16:56:32 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	remove_arg(char **args, int index)
{
	int	i;

	i = index;
	while (args[i])
	{
		args[i] = args[i + 1];
		i++;
	}
}

void	expand_args(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->args[i])
	{
		expanded = expand_string(cmd->args[i], shell);
		if (expanded)
		{
			free(cmd->args[i]);
			cmd->args[i] = expanded;
			if (cmd->args[i][0] == '\0')
			{
				free(cmd->args[i]);
				remove_arg(cmd->args, i);
				continue ;
			}
		}
		i++;
	}
}

void	expand_redirs(t_redir *redir, t_shell *shell)
{
	char	*expanded;

	while (redir)
	{
		if (redir->type != REDIR_HEREDOC && redir->file)
		{
			expanded = expand_string(redir->file, shell);
			if (expanded)
			{
				free(redir->file);
				redir->file = expanded;
			}
		}
		redir = redir->next;
	}
}

void	expand_commands(t_cmd *cmd, t_shell *shell)
{
	while (cmd)
	{
		if (cmd->args)
			expand_args(cmd, shell);
		if (cmd->args)
			split_command_args(cmd);
		if (cmd->redirs)
			expand_redirs(cmd->redirs, shell);
		cmd = cmd->next;
	}
}
