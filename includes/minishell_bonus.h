#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

# include "token.h"

void	create_operator_token(t_token_type type, t_token **head,
			t_token **current, int *i);

#endif
