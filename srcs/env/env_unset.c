#include "../../includes/minishell.h"

int	unset_env_value(char *key, t_shell *shell)
{
	t_env	*prev;
	t_env	*curr;

	if (!key || !shell || !shell->env_list)
		return (0);
	prev = NULL;
	curr = shell->env_list;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				shell->env_list = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			env_list_to_array(shell);
			return (1);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}
