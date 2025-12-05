#ifndef DEBUG_H
# define DEBUG_H

# include "minishell.h"

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

#endif
