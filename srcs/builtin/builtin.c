/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:54:26 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/28 16:54:27 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	builtin_colon(char **args)
{
	(void)args;
	return (0);
}

static int	is_number_str(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	builtin_arith(char **args, t_shell *shell)
{
	char		*trim;
	char		*value;
	long long	num;
	int			overflow;

	if (!args || !args[1])
		return (1);
	trim = ft_strtrim(args[1], " \t\n");
	if (!trim || !*trim)
		return (free(trim), 1);
	value = trim;
	if (!is_number_str(trim))
		value = get_env_value(trim, shell);
	overflow = 0;
	num = 0;
	if (value && *value)
		num = ft_atoll(value, &overflow);
	free(trim);
	if (overflow || num == 0)
		return (1);
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, ":") == 0
		|| ft_strcmp(cmd, "__arith__") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (builtin_echo(cmd->args));
	else if (ft_strcmp(cmd->args[0], ":") == 0)
		return (builtin_colon(cmd->args));
	else if (ft_strcmp(cmd->args[0], "__arith__") == 0)
		return (builtin_arith(cmd->args, shell));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (builtin_cd(cmd->args, shell));
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (builtin_export(cmd->args, shell));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (builtin_unset(cmd->args, shell));
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (builtin_env(cmd->args, shell));
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (builtin_exit(cmd->args, shell));
	return (0);
}
