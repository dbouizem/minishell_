/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:10:00 by dbouizem          #+#    #+#             */
/*   Updated: 2025/12/08 17:10:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell_bonus.h"

void	skip_spaces_bonus(t_token **tokens)
{
	while (*tokens && (*tokens)->type == SPACES)
		*tokens = (*tokens)->next;
}

t_ast	*create_ast_node_bonus(t_ast_type type, t_cmd *pipeline,
		t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (parse_memory_error("ast_node"), NULL);
	node->type = type;
	node->pipeline = pipeline;
	node->redirs = NULL;
	node->left = left;
	node->right = right;
	return (node);
}

t_ast	*parse_ast_bonus(t_token *tokens, t_shell *shell)
{
	t_token	*cursor;
	t_ast	*ast;

	cursor = tokens;
	ast = parse_logical_bonus(&cursor, shell);
	if (!ast)
		return (NULL);
	skip_spaces_bonus(&cursor);
	if (cursor)
	{
		parse_syntax_error(&cursor, shell);
		free_ast_bonus(ast);
		return (NULL);
	}
	return (ast);
}
