#ifndef EXPANDER_H
# define EXPANDER_H

# include "parser.h"
# include "minishell.h"

typedef struct s_shell	t_shell;

void	expand_commands(t_cmd *cmd, t_shell *shell);

char	*get_var_value(char *var_name, t_shell *shell);

char	*remove_quotes(char *str);

int		is_valid_var_char(char c);
int		is_valid_var_start_char(char c);
char	*ft_strjoin_free(char *s1, char *s2);
char	*char_to_str(char c);

char	*expand_string(char *str, t_shell *shell);

char	*process_dollar(char *str, int *i, t_shell *shell);
char	*process_normal_char(char *str, int *i, int in_quotes);
char	*extract_var_name(char *str, int *i, t_shell *shell);
char	*extract_single_quoted_content(char *str, int *i);

#endif
