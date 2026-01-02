#ifndef BONUS_H
# define BONUS_H

# include "minishell.h"
# include "wildcard.h"

void	create_operator_token(t_token_type type, t_token **head,
			t_token **current, int *i);
int		is_separator(t_token *token);
int		is_command_separator(t_token_type type);
int		execute(t_cmd *cmd, t_shell *shell);
int		execute_command(t_cmd *cmd, t_shell *shell);

#endif