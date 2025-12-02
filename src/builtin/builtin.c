#include "../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	int	exit_status;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	exit_status = 0;
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		exit_status = builtin_echo(cmd->args);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		exit_status = builtin_pwd();
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		exit_status = builtin_cd(cmd->args, shell);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		exit_status = builtin_export(cmd->args, shell);/*
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		exit_status = builtin_unset(cmd->args, shell);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		exit_status = builtin_env(shell);*/
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		exit_status = builtin_exit(cmd->args, shell);
	return (exit_status);
}