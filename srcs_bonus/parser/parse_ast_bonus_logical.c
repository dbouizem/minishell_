/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast_bonus_logical.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:10:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/30 15:36:53 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell_bonus.h"

static t_redir	*parse_subshell_redirs(t_token **tokens, t_shell *shell,
		int *ok)
{
	t_redir	*head;
	t_redir	*redir;

	head = NULL;
	*ok = 1;
	skip_spaces_bonus(tokens);
	while (*tokens && is_redir((*tokens)->type))
	{
		redir = parse_redirection(tokens, shell);
		if (!redir)
		{
			*ok = 0;
			return (free_redirs(head), NULL);
		}
		add_redir(&head, redir);
		skip_spaces_bonus(tokens);
	}
	return (head);
}

static t_ast	*parse_parenthesis_bonus(t_token **tokens, t_shell *shell)
{
	t_ast	*inner;
	t_ast	*node;
	t_redir	*redirs;
	int		ok;

	*tokens = (*tokens)->next;
	inner = parse_logical_bonus(tokens, shell);
	if (!inner)
		return (NULL);
	skip_spaces_bonus(tokens);
	if (!*tokens || (*tokens)->type != PAREN_CLOSE)
		return (free_ast_bonus(inner),
			parse_syntax_error(tokens, shell), NULL);
	*tokens = (*tokens)->next;
	redirs = parse_subshell_redirs(tokens, shell, &ok);
	if (!ok)
		return (free_ast_bonus(inner), NULL);
	node = create_ast_node_bonus(AST_SUBSHELL, NULL, inner, NULL);
	if (!node)
		return (free_ast_bonus(inner), free_redirs(redirs), NULL);
	node->redirs = redirs;
	return (node);
}

t_ast	*parse_primary_bonus(t_token **tokens, t_shell *shell)
{
	t_cmd	*pipeline;
	t_ast	*node;

	skip_spaces_bonus(tokens);
	if (!*tokens)
		return (parse_syntax_error(tokens, shell), NULL);
	if ((*tokens)->type == PAREN_OPEN)
		return (parse_parenthesis_bonus(tokens, shell));
	if ((*tokens)->type == AND || (*tokens)->type == OR
		|| (*tokens)->type == PIPE || (*tokens)->type == PAREN_CLOSE)
		return (parse_syntax_error(tokens, shell), NULL);
	pipeline = parse_pipeline_bonus(tokens, shell);
	if (!pipeline)
		return (NULL);
	node = create_ast_node_bonus(AST_PIPELINE, pipeline, NULL, NULL);
	if (!node)
	{
		if (shell)
			shell->exit_status = 1;
		free_cmd(pipeline);
		return (NULL);
	}
	return (node);
}

static t_ast	*join_logical_node(t_token_type op, t_ast *left, t_ast *right,
		t_shell *shell)
{
	t_ast	*node;

	if (op == AND)
		node = create_ast_node_bonus(AST_AND, NULL, left, right);
	else
		node = create_ast_node_bonus(AST_OR, NULL, left, right);
	if (!node)
	{
		if (shell)
			shell->exit_status = 1;
		return (free_ast_bonus(left), free_ast_bonus(right), NULL);
	}
	return (node);
}

t_ast	*parse_logical_bonus(t_token **tokens, t_shell *shell)
{
	t_ast			*left;
	t_ast			*right;
	t_token_type	op;

	left = parse_primary_bonus(tokens, shell);
	if (!left)
		return (NULL);
	skip_spaces_bonus(tokens);
	while (*tokens && ((*tokens)->type == AND || (*tokens)->type == OR))
	{
		op = (*tokens)->type;
		*tokens = (*tokens)->next;
		right = parse_primary_bonus(tokens, shell);
		if (!right)
			return (free_ast_bonus(left), NULL);
		left = join_logical_node(op, left, right, shell);
		if (!left)
			return (NULL);
		skip_spaces_bonus(tokens);
	}
	return (left);
}
