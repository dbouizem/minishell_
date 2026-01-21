#ifndef BUILTIN_H
# define BUILTIN_H

typedef struct s_cmd	t_cmd;
typedef struct s_shell	t_shell;
typedef struct s_env	t_env;

int		is_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd, t_shell *shell);

int		builtin_echo(char **args);
int		builtin_pwd(void);
int		builtin_exit(char **args, t_shell *shell);
int		builtin_cd(char **args, t_shell *shell);

int		builtin_env(char **args, t_shell *shell);
int		builtin_export(char **args, t_shell *shell);
int		builtin_unset(char **args, t_shell *shell);

void	print_cd_error(char *arg, char *msg);
void	print_export_error(char *arg);
void	print_unset_error(char *arg);
void	print_env_error(char *arg);
void	print_exit_error(char *arg, char *error_type);

void	print_env(t_shell *shell);
t_env	*dup_env_list(t_env *env_list);
int		apply_env_assignment(t_env **env_list, char *arg);
int		print_env_list(t_env *env_list);
void	print_exported_vars(t_shell *shell);

#endif
