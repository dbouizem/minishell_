#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <termios.h>
# include <errno.h>

# include "../libft/libft.h"
# include "colors.h"
# include "token.h"
# include "parser.h"
# include "expander.h"

// Structure principale
typedef struct s_shell
{
	char			**env;
	int				exit_status;
	int				interactive; //  0 ou 1  isatty()
	struct termios	original_term; // SAUVEGARDE DU TERMINAL
}	t_shell;

void	init_shell(t_shell *shell, char **envp);
void	cleanup_shell(t_shell *shell);
char	*read_input(void);
void	display_welcome(void);
int		process_input(char *input, t_shell *shell);

#endif
