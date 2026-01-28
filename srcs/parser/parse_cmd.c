/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:58:03 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/28 16:58:04 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	append_arg_copy(t_cmd *cmd, char *dup, int count)
{
	char	**new_args;
	int		i;

	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (free(dup), 0);
	i = 0;
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[count] = dup;
	new_args[count + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	return (1);
}

static int	append_arg(t_cmd *cmd, char *value)
{
	char	*dup;
	int		count;

	if (!cmd || !value)
		return (0);
	dup = ft_strdup(value);
	if (!dup)
		return (0);
	count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
			count++;
	}
	return (append_arg_copy(cmd, dup, count));
}

static int	handle_args(t_token **tokens, t_cmd *cmd)
{
	cmd->args = parse_arguments(tokens);
	if (!cmd->args)
	{
		if (!cmd->redirs)
			return (0);
		cmd->args = malloc(sizeof(char *));
		if (!cmd->args)
			return (0);
		cmd->args[0] = NULL;
	}
	return (1);
}

static int	handle_remaining_redirs(t_token **tokens, t_cmd *cmd,
		t_shell *shell)
{
	t_redir	*redir;

	while (*tokens && !is_command_separator((*tokens)->type))
	{
		if (is_redir((*tokens)->type))
		{
			redir = parse_redirection(tokens, shell);
			if (!redir)
				return (0);
			add_redir(&cmd->redirs, redir);
			continue ;
		}
		if ((*tokens)->type == WORD
			&& !append_arg(cmd, (*tokens)->value))
			return (0);
		*tokens = (*tokens)->next;
	}
	return (1);
}

t_cmd	*parse_command(t_token **tokens, t_shell *shell)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = create_cmd();
	if (!cmd)
		return (NULL);
	while (*tokens && !is_command_separator((*tokens)->type)
		&& is_redir((*tokens)->type))
	{
		redir = parse_redirection(tokens, shell);
		if (!redir)
			return (free_cmd(cmd), NULL);
		add_redir(&cmd->redirs, redir);
		while (*tokens && (*tokens)->type == SPACES)
			*tokens = (*tokens)->next;
	}
	if (!handle_args(tokens, cmd))
		return (free_cmd(cmd), NULL);
	if (!handle_remaining_redirs(tokens, cmd, shell))
		return (free_cmd(cmd), NULL);
	return (cmd);
}
