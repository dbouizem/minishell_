#include "../../includes/minishell.h"

void	debug_env_list(t_env *env)
{
	printf("=== Environment List ===\n");
	while (env)
	{
		printf("%s=%s\n", env->key, env->value ? env->value : "(null)");
		env = env->next;
	}
	printf("=======================\n");
}
