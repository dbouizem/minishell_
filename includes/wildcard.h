#ifndef WILDCARD_H
# define WILDCARD_H

# include "minishell.h"
# include <dirent.h>

typedef struct s_wildcard
{
	char				*match;
	struct s_wildcard	*next;
}	t_wildcard;

int			has_wildcard(char *str);
t_wildcard	*expand_wildcard(char *pattern);
void		process_wildcards(t_cmd *cmd);
int			match_pattern(const char *pattern, const char *str);
t_wildcard	*create_wildcard_node(char *match);
void		add_wildcard_sorted(t_wildcard **head, t_wildcard *new_node);
void		free_wildcard_list(t_wildcard *list);
int			count_wildcard_matches(t_wildcard *list);
char		**wildcard_list_to_array(t_wildcard *list);

#endif