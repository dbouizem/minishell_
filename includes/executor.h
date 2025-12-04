// includes/executor.h
#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

int		execute(t_cmd *cmd, t_shell *shell);
int		execute_command(t_cmd *cmd, t_shell *shell);
int		execute_pipeline(t_cmd *cmd, t_shell *shell);

int		is_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd, t_shell *shell);
int		ft_echo(t_cmd *cmd);
int		ft_cd(t_cmd *cmd, t_shell *shell);
int		ft_pwd(void);
int		ft_export(t_cmd *cmd, t_shell *shell);
int		ft_unset(t_cmd *cmd, t_shell *shell);
int		ft_env(t_shell *shell);
int		ft_exit(t_cmd *cmd, t_shell *shell);

int		execute_external(t_cmd *cmd, t_shell *shell);
void	execute_external_no_fork(t_cmd *cmd, t_shell *shell);
char	*find_command_path(char *cmd, t_shell *shell);
void	execute_command_child(t_cmd *cmd, t_shell *shell);


int		setup_redirections(t_cmd *cmd);

void	remove_quotes_from_command(t_cmd *cmd);
void	handle_exec_error(char *cmd, t_shell *shell);
int		save_redirections(int *saved_stdin, int *saved_stdout);
int		restore_redirections(int saved_stdin, int saved_stdout);


#endif
