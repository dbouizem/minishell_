#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

// Structure principale
typedef struct s_shell
{
	char	**env;
	int		exit_status;
}	t_shell;

// Prototypes
void	init_shell(t_shell *shell, char **envp);
void	cleanup_shell(t_shell *shell);
void	display_prompt(void);
char	*read_input(void);

#endif
