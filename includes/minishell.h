#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <readline/rlconf.h>
# include <readline/rltypedefs.h>
# include <unistd.h>
# include <termios.h>
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>

# include "../libft/libft.h"
# include "colors.h"
# include "token.h"
# include "parser.h"
# include "expander.h"
# include "executor.h"
# include "builtin.h"
# include "env.h"

extern volatile sig_atomic_t	g_signal;

typedef struct s_shell
{
	char			**env;
	t_env			*env_list;
	int				exit_status;
	int				interactive;
	struct termios	original_term;
	int				num_pipes;
}	t_shell;

void	init_shell(t_shell *shell, char **envp);
void	cleanup_shell(t_shell *shell);

void	setup_signals(void);
void	setup_child_signals(void);

char	*read_input(void);
char	*read_input_non_interactive(void);
int		process_input(char *input, t_shell *shell);

void	shell_error(char *message, int exit_code);
void	process_error(char *context, t_shell *shell);
void	*check_malloc(void *ptr, char *context);

#endif
