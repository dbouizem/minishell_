// includes/minishell.h
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <termios.h>
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "../libft/libft.h"
# include "colors.h"
# include "token.h"
# include "parser.h"
# include "expander.h"
# include "executor.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

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

char	*read_input(void);
char	*read_input_non_interactive(void);
void	display_welcome(void);

int		process_input(char *input, t_shell *shell);

void	env_list_to_array(t_shell *shell);
char	*get_env_value(char *key, t_shell *shell);
void	update_env_var(char *key, char *value, t_shell *shell);

#endif
