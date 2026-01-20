/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:28:00 by dbouizem          #+#    #+#             */
/*   Updated: 2025/12/08 18:28:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell_bonus.h"

static int	set_exit_status(t_shell *shell, int status)
{
	if (shell)
		shell->exit_status = status;
	return (status);
}

static int	execute_pipeline_node(t_cmd *pipeline, t_shell *shell)
{
	int	status;

	if (!pipeline)
		return (set_exit_status(shell, 1));
	expand_commands(pipeline, shell);
	expand_wildcards(pipeline);
	remove_quotes_from_command(pipeline);
	status = execute_pipeline(pipeline, shell);
	return (set_exit_status(shell, status));
}

static int	execute_logical_node(t_ast *ast, t_shell *shell)
{
	int	status;

	status = execute_ast_bonus(ast->left, shell);
	if (shell && shell->should_exit)
		return (shell->exit_status);
	if (ast->type == AST_AND && status == 0)
		status = execute_ast_bonus(ast->right, shell);
	else if (ast->type == AST_OR && status != 0)
		status = execute_ast_bonus(ast->right, shell);
	return (set_exit_status(shell, status));
}

int	execute_ast_bonus(t_ast *ast, t_shell *shell)
{
	if (!ast)
		return (set_exit_status(shell, 1));
	if (shell && shell->should_exit)
		return (shell->exit_status);
	if (ast->type == AST_PIPELINE)
		return (execute_pipeline_node(ast->pipeline, shell));
	return (execute_logical_node(ast, shell));
}

void	free_ast_bonus(t_ast *ast)
{
	if (!ast)
		return ;
	free_ast_bonus(ast->left);
	free_ast_bonus(ast->right);
	if (ast->type == AST_PIPELINE)
		free_cmd(ast->pipeline);
	free(ast);
}
