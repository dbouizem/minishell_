#include "../includes/minishell.h"

static void	print_args_list(char **args)
{
	int		i;
	char	*trimmed;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		trimmed = ft_strtrim(args[i], "\n\r");
		printf("'%s'", trimmed);
		free(trimmed);
		if (args[i + 1])
			printf(", ");
		i++;
	}
}

static void	print_redir_list(t_redir *redir)
{
	const char	*symbols[] = {"", "", "", "", "", "<", ">", "<<", ">>"};

	if (!redir)
		return ;
	printf("  Redirs: ");
	while (redir)
	{
		printf("%s '%s'", symbols[redir->type], redir->file);
		redir = redir->next;
		if (redir)
			printf(", ");
	}
	printf("\n");
}

void	print_cmd(t_cmd *cmd)
{
	printf("\n%s=== PARSED COMMANDS ===%s\n", CYAN, RESET);
	while (cmd)
	{
		printf("%s[Command]%s\n", GREEN, RESET);
		printf("  Args: [");
		print_args_list(cmd->args);
		printf("]\n");
		if (cmd->redirs)
			print_redir_list(cmd->redirs);
		cmd = cmd->next;
		if (cmd)
			printf("  %s|%s\n", YELLOW, RESET);
	}
	printf("%s========================%s\n\n", CYAN, RESET);
}
