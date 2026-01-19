/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:10:00 by dbouizem          #+#    #+#             */
/*   Updated: 2025/12/08 18:10:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_command_separator(t_token_type type)
{
	return (type == PIPE || type == AND || type == OR
		|| type == PAREN_OPEN || type == PAREN_CLOSE);
}

int	is_separator(t_token *tokens)
{
	if (tokens->type == PIPE)
		return (1);
	if (tokens->type == AND || tokens->type == OR)
		return (1);
	if (tokens->type == PAREN_OPEN || tokens->type == PAREN_CLOSE)
		return (1);
	return (0);
}

t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->separator = 0;
	cmd->next = NULL;
	return (cmd);
}

t_redir	*create_redir(t_redir_type type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
	{
		free(file);
		return (NULL);
	}
	redir->type = type;
	redir->file = file;
	redir->fd = -1;
	redir->next = NULL;
	return (redir);
}
