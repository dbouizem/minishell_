/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:58:13 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/28 16:58:14 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	add_command_to_list(t_cmd **head, t_cmd **current, t_cmd *new_cmd)
{
	if (!*head)
	{
		*head = new_cmd;
		*current = *head;
	}
	else
	{
		(*current)->next = new_cmd;
		*current = (*current)->next;
	}
}

static void	skip_sep_token(t_token **tokens, t_cmd *cmd)
{
	if (*tokens && is_separator(*tokens))
	{
		cmd->separator = (*tokens)->type;
		*tokens = (*tokens)->next;
	}
	else
		cmd->separator = 0;
}

static int	check_final_sep(t_token *tokens, t_cmd *head, t_shell *shell)
{
	if (tokens && is_separator(tokens) && !tokens->next)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ",
			STDERR_FILENO);
		ft_putstr_fd(tokens->value, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		shell->exit_status = 2;
		free_cmd(head);
		return (0);
	}
	return (1);
}

static t_cmd	*process_tokens(t_token *tokens, t_shell *shell)
{
	t_cmd	*head;
	t_cmd	*current;
	t_cmd	*new_cmd;

	head = NULL;
	current = NULL;
	while (tokens)
	{
		new_cmd = parse_command(&tokens, shell);
		if (!new_cmd)
		{
			if (head)
				free_cmd(head);
			return (NULL);
		}
		add_command_to_list(&head, &current, new_cmd);
		if (!check_final_sep(tokens, head, shell))
			return (NULL);
		skip_sep_token(&tokens, current);
	}
	return (head);
}

t_cmd	*parse(t_token *tokens, t_shell *shell)
{
	t_cmd	*head;

	if (!tokens)
		return (NULL);
	head = process_tokens(tokens, shell);
	if (!head)
		return (NULL);
	if (!check_parser_syntax(tokens, head, shell))
		return (free_cmd(head), NULL);
	return (head);
}
