#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

int		is_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd, t_shell *shell);

int		builtin_echo(char **args);
int		builtin_pwd(void);
int		builtin_exit(char **args, t_shell *shell);

int		builtin_cd(char **args, t_shell *shell);
int		builtin_export(char **args, t_shell *shell);
int		builtin_unset(char **args, t_shell *shell);
int		builtin_env(t_shell *shell);

char	*get_env_value(char *key, t_shell *shell);
int		set_env_value(char *key, char *value, t_shell *shell);
int		unset_env_value(char *key, t_shell *shell);
void	print_env(t_shell *shell);

#endif