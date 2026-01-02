#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

typedef enum e_token_type
{
	SPACES = 1,
	WORD,
	AND,
	OR,
	PIPE,
	INPUT,
	TRUNC,
	HEREDOC,
	APPEND,
	INVALID,
}	t_token_type;

typedef struct	s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;


t_token			*tokenize(char *input);
t_token			*create_token(t_token_type type, char *value);
void			add_token(t_token **head, t_token **current,
					t_token *new_token);
void			free_tokens(t_token *tokens);

int				is_whitespace(char c);
int				is_special_char(char c);
int				is_quote(char c);
int				is_redir(t_token_type type);
int				is_forbidden_char(char c);

void			handle_spaces(char *input, int *i,
					t_token **head, t_token **current);
void			handle_word(char *input, int *i, t_token **head,
					t_token **current);
void			handle_pipe_or_redir(char *input, int *i,
					t_token **head, t_token **current);
char			*extract_word_without_quotes(char *input, int *i);
t_token_type	get_redir_type(char *input, int i);

char			*extract_substring(char *input, int start, int end);

int				has_quote_error(char *input);
int				lexer_quote_error(char quote);
void			lexer_memory_error(char *context);
void			lexer_syntax_error(char *token);

#endif
