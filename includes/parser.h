#ifndef PARSER_H
# define PARSER_H

# include "token.h"

typedef struct s_shell	t_shell;

typedef enum e_redir_type
{
	REDIR_NONE = 0,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	int				separator;
	struct s_cmd	*next;
}	t_cmd;

t_cmd		*parse(t_token *tokens, t_shell *shell);
t_cmd		*parse_command(t_token **tokens, t_shell *shell);

char		**parse_arguments(t_token **tokens);
int			count_args(t_token *tokens);

t_redir		*parse_redirection(t_token **tokens, t_shell *shell);
void		add_redir(t_redir **head, t_redir *new_redir);

t_cmd		*create_cmd(void);
t_redir		*create_redir(t_redir_type type, char *file);

void		free_cmd(t_cmd *cmd);
void		free_redirs(t_redir *redirs);

int			check_parser_syntax(t_token *tokens, t_cmd *cmds, t_shell *shell);

void		parse_syntax_error(t_token **tokens, t_shell *shell);
void		pipe_syntax_error(t_shell *shell);
void		redir_syntax_error(t_shell *shell);
int			parse_memory_error(char *context);

int			is_command_separator(t_token_type type);
int			is_separator(t_token *tokens);
void		create_operator_token(t_token_type type, t_token **head,
				t_token **current, int *i);

#endif
