/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:45:00 by dbouizem          #+#    #+#             */
/*   Updated: 2025/12/08 17:45:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

# include "token.h"

typedef struct s_cmd	t_cmd;
typedef struct s_shell	t_shell;

typedef enum e_ast_type
{
	AST_PIPELINE = 1,
	AST_AND,
	AST_OR
}	t_ast_type;

typedef struct s_ast
{
	t_ast_type		type;
	t_cmd			*pipeline;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

void	create_operator_token(t_token_type type, t_token **head,
			t_token **current, int *i);
t_ast	*parse_ast_bonus(t_token *tokens, t_shell *shell);
t_ast	*parse_logical_bonus(t_token **tokens, t_shell *shell);
t_ast	*parse_primary_bonus(t_token **tokens, t_shell *shell);
t_cmd	*parse_pipeline_bonus(t_token **tokens, t_shell *shell);
t_ast	*create_ast_node_bonus(t_ast_type type, t_cmd *pipeline,
			t_ast *left, t_ast *right);
void	skip_spaces_bonus(t_token **tokens);
int		execute_ast_bonus(t_ast *ast, t_shell *shell);
void	free_ast_bonus(t_ast *ast);

#endif
