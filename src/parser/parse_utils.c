#include "../includes/minishell.h"

t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_redir	*create_redir(int type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
	{
		free(file);
		return (NULL);
	}
	redir->type = type;
	redir->file = file;
	redir->next = NULL;
	return (redir);
}

static void	print_args_list(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		printf("'%s'", args[i]);
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
