#ifndef ENV_H
# define ENV_H

typedef struct s_shell	t_shell;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

t_env	*env_array_to_list(char **envp);
void	env_list_to_array(t_shell *shell);
void	free_env_list(t_env *env);

char	*get_env_value(char *key, t_shell *shell);
void	update_env_var(char *key, char *value, t_shell *shell);
int		set_env_value(char *key, char *value, t_shell *shell);
int		unset_env_value(char *key, t_shell *shell);
void	init_minimal_env(t_shell *shell, char *argv0);

int		is_valid_env_key(char *key);
void	env_error(char *key, char *message);

#endif
