#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

int		is_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd, t_shell *shell);

int		builtin_echo(char **args);
int		builtin_pwd(void);
int		builtin_exit(char **args, t_shell *shell);

#endif