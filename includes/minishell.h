#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

# include "../libft/libft.h"
# include "colors.h"
# include "token.h"
# include "parser.h"

// Structure principale
typedef struct s_shell
{
	char	**env;
	int		exit_status;
}	t_shell;

// Prototypes
void	init_shell(t_shell *shell, char **envp);
void	cleanup_shell(t_shell *shell);
char	*read_input(void);
int		handle_input(char *input, t_shell *shell);

#endif
