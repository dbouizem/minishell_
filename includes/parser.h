#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct	s_shell t_shell;

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

t_cmd	*parse(t_token *tokens, t_shell *shell);
t_cmd	*parse_command(t_token **tokens, t_shell *shell);
char	**parse_arguments(t_token **tokens);
int		count_args(t_token *tokens);
t_redir	*parse_redirection(t_token **tokens, t_shell *shell);
void	add_redir(t_redir **head, t_redir *new_redir);
t_cmd	*create_cmd(void);
t_redir	*create_redir(int type, char *file);
void	free_cmd(t_cmd *cmd);
void	free_redirs(t_redir *redirs);
void	print_cmd(t_cmd *cmd);
int		check_parser_syntax(t_token *tokens, t_cmd *cmds, t_shell *shell);

#endif
