#ifndef DEBUG_H
# define DEBUG_H

# include <sys/types.h>

typedef struct s_cmd	t_cmd;
typedef struct s_shell	t_shell;
typedef struct s_token	t_token;
typedef struct s_env	t_env;

void	print_command(t_cmd *cmd, int cmd_num);
void	print_pipeline(t_cmd *cmd);
void	print_expansion_debug(t_cmd *cmd, const char *phase);
void	print_fd_debug(const char *context);
void	print_execution_step(const char *step, t_cmd *cmd, t_shell *shell);

void	print_tokens(t_token *tokens);
void	debug_lexer_parser(t_token *tokens, t_cmd *cmds, t_shell *shell);
void	print_cmd(t_cmd *cmd);
void	debug_env_list(t_env *env);
void	debug_executor(t_cmd *cmd, t_shell *shell, const char *phase);
void	debug_fork_header(int total_cmds);
void	debug_fork_command(int index, t_cmd *cmd);
void	debug_fork_parent(int index, pid_t pid);
void	debug_fork_footer(void);

#endif
