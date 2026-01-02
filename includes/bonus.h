#ifndef BONUS_H
# define BONUS_H

# include "minishell.h"

/*
** ============================================================================
** BONUS FEATURES
** ============================================================================
** This header contains declarations for bonus features:
** - Logical operators: && (AND) and || (OR)
** - Conditional command execution based on exit status
** ============================================================================
*/

/*
** ============================================================================
** LEXER BONUS FUNCTIONS
** ============================================================================
*/

/* Create token for logical operators (&&, ||) */
void	create_operator_token(t_token_type type, t_token **head,
			t_token **current, int *i);

/*
** ============================================================================
** PARSER BONUS FUNCTIONS
** ============================================================================
*/

/* Check if token is a command separator (|, &&, ||) */
int		is_separator(t_token *token);

/* Check if token type is a command separator */
int		is_command_separator(t_token_type type);

/*
** ============================================================================
** EXECUTOR BONUS FUNCTIONS
** ============================================================================
*/

/* Execute commands with conditional logic (&&, ||) */
int		execute(t_cmd *cmd, t_shell *shell);

/* Execute a single command with redirections */
int		execute_command(t_cmd *cmd, t_shell *shell);

#endif