/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:53:41 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/28 16:53:42 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# define EXP_QUOTE_SQ 0x1F
# define EXP_QUOTE_DQ 0x1E

typedef struct s_cmd	t_cmd;
typedef struct s_shell	t_shell;

typedef struct s_state
{
	int	in_single;
	int	in_double;
}	t_state;

void	expand_commands(t_cmd *cmd, t_shell *shell);
char	*expand_string(char *str, t_shell *shell);

char	*get_var_value(char *var_name, t_shell *shell);
char	*extract_var_name(char *str, int *i, t_shell *shell);

char	*process_dollar(char *str, int *i, t_shell *shell);
char	*handle_special_chars(char *str, int *i, t_shell *shell);
char	*handle_dollar_basic_cases(char *str, int *i);
char	*handle_curly_brace_syntax(char *str, int *i, t_shell *shell);
char	*handle_normal_var(char *str, int *i);
char	*extract_curly_var_name(char *str, int *i, int start);
int		count_fields(char *str);
char	**split_fields(char *str);
void	split_command_args(t_cmd *cmd);

char	*remove_quotes(char *str);
void	remove_quotes_from_command(t_cmd *cmd);
int		handle_quotes_flags(char c, t_state *state);

char	*process_normal_char(char *str, int *i, int in_quotes);
char	*extract_single_quoted_content(char *str, int *i);

int		is_valid_var_char(char c);
int		is_valid_var_start_char(char c);
char	*ft_strjoin_free(char *s1, char *s2);
char	*char_to_str(char c);

#endif
