#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token_type
{
	SPACES = 1,
	WORD,
	VAR,
	PIPE,
	INPUT,
	TRUNC,
	HEREDOC,
	APPEND,
	END
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

/* tokenize.c */
t_token			*tokenize(char *input);

/* token_utils.c */
t_token			*create_token(t_token_type type, char *value);
void			add_token(t_token **head, t_token **current, t_token *new_token);
void			free_tokens(t_token *tokens);
void			print_tokens(t_token *tokens);

/* lexer_checks.c */
int				is_whitespace(char c);
int				is_special_char(char c);
int				is_quote(char c);

/* lexer_extract.c */
char			*extract_substring(char *input, int start, int end);
void			handle_quotes(char *input, int *i);

/* lexer_handlers.c */
void			handle_spaces(char *input, int *i, t_token **head, t_token **current);
void			handle_variable(char *input, int *i, t_token **head, t_token **current);
void			handle_word(char *input, int *i, t_token **head, t_token **current);

/* lexer_redir.c */
t_token_type	get_redir_type(char *input, int i);
void			handle_pipe_or_redir(char *input, int *i, t_token **head,
					t_token **current);

#endif
