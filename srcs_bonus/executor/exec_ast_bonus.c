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
	if (shell)
		shell->exit_status = status;
	return (status);
}

static void	execute_subshell_child(t_ast *ast, t_shell *shell)
{
	int		status;
	int		redir_status;
	t_cmd	cmd;

	setup_child_signals();
	redir_status = 0;
	if (ast->redirs)
	{
		ft_bzero(&cmd, sizeof(t_cmd));
		cmd.redirs = ast->redirs;
		redir_status = setup_redirections(&cmd, shell);
	}
	if (redir_status == 130)
		exit_child(130, shell);
	if (redir_status != 0)
		exit_child(1, shell);
	status = execute_ast_bonus(ast->left, shell);
	exit_child(status, shell);
}

static int	execute_subshell_node(t_ast *ast, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork_process();
	if (pid == 0)
		execute_subshell_child(ast, shell);
	if (pid == -1)
	{
		if (shell)
			shell->exit_status = 1;
		return (1);
	}
	wait_for_child(pid, &status, shell);
	if (shell)
		return (shell->exit_status);
	return (1);
}

int	execute_ast_bonus(t_ast *ast, t_shell *shell)
{
	if (!ast)
	{
		if (shell)
			shell->exit_status = 1;
		return (1);
	}
	if (shell && shell->should_exit)
		return (shell->exit_status);
	if (ast->type == AST_PIPELINE)
	{
		expand_commands(ast->pipeline, shell);
		expand_wildcards(ast->pipeline);
		remove_quotes_from_command(ast->pipeline);
		shell->exit_status = execute_pipeline(ast->pipeline, shell);
		return (shell->exit_status);
	}
	if (ast->type == AST_SUBSHELL)
		return (execute_subshell_node(ast, shell));
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
	if (ast->redirs)
		free_redirs(ast->redirs);
	free(ast);
}
