/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast_bonus_pipeline.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:10:00 by dbouizem          #+#    #+#             */
/*   Updated: 2025/12/08 17:10:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell_bonus.h"

static int	invalid_token(t_token *token)
{
	if (!token)
		return (1);
	if (token->type == AND || token->type == OR || token->type == PIPE
		|| token->type == PAREN_CLOSE || token->type == PAREN_OPEN)
		return (1);
	return (0);
}

static int	parse_and_append_cmd(t_cmd **head, t_cmd **current,
		t_token **tokens, t_shell *shell)
{
	t_cmd	*cmd;

	cmd = parse_command(tokens, shell);
	if (!cmd)
		return (free_cmd(*head), 0);
	if ((!cmd->args || !cmd->args[0]) && !cmd->redirs)
	{
		free_cmd(cmd);
		free_cmd(*head);
		parse_syntax_error(tokens, shell);
		return (0);
	}
	if (!*head)
		*head = cmd;
	else
		(*current)->next = cmd;
	*current = cmd;
	return (1);
}

static int	handle_separator(t_cmd *head, t_cmd *current,
		t_token **tokens, t_shell *shell)
{
	if (!*tokens)
		return (0);
	if ((*tokens)->type == PIPE)
	{
		current->separator = PIPE;
		*tokens = (*tokens)->next;
		skip_spaces_bonus(tokens);
		if (invalid_token(*tokens))
			return (free_cmd(head),
				parse_syntax_error(tokens, shell), -1);
		return (1);
	}
	if ((*tokens)->type == PAREN_OPEN)
		return (free_cmd(head),
			parse_syntax_error(tokens, shell), -1);
	if ((*tokens)->type == AND || (*tokens)->type == OR
		|| (*tokens)->type == PAREN_CLOSE)
		return (0);
	return (0);
}

t_cmd	*parse_pipeline_bonus(t_token **tokens, t_shell *shell)
{
	t_cmd	*head;
	t_cmd	*current;
	int		action;

	head = NULL;
	current = NULL;
	skip_spaces_bonus(tokens);
	if (invalid_token(*tokens))
		return (parse_syntax_error(tokens, shell), NULL);
	while (*tokens)
	{
		if (!parse_and_append_cmd(&head, &current, tokens, shell))
			return (NULL);
		skip_spaces_bonus(tokens);
		action = handle_separator(head, current, tokens, shell);
		if (action == -1)
			return (NULL);
		if (action == 0)
			break ;
	}
	return (head);
}
