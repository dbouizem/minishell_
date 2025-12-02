/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:45:24 by fadzejli          #+#    #+#             */
/*   Updated: 2025/12/02 14:50:21 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static void	update_pwd(char *old_pwd, t_shell *shell)
{
	char cwd[2064];

	if (old_pwd)
		set_env_value("OLDPWD", old_pwd, shell);
	if (getcwd(cwd, sizeof(cwd)))
		set_env_value("PWD", cwd, shell);
}

static int	cd_home(t_shell *shell, char *old_pwd)
{
	char *home;

	home = get_env_value("HOME", shell);
	if (!home)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		if (old_pwd)
			free(old_pwd);
		return (1);
	}
	if (chdir(home) == -1)
	{
		perror("minishell: cd");
		if (old_pwd)
			free(old_pwd);
		return (1);
	}
	update_pwd(old_pwd, shell);
	return (0);
}


int	builtin_cd(char **args, t_shell *shell)
{
	char	*old_pwd;
	int		exit_status;

	exit_status = 0;
	old_pwd = getcwd(NULL, 0);
	if (!args[1] || !*args[1])
		return (cd_home(shell, old_pwd));
	if (args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		exit_status = 1;
	}
	else if (chdir(args[1]) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		exit_status = 1;
	}
	else
		update_pwd(old_pwd, shell);
	if (old_pwd)
		free(old_pwd);
	return (exit_status);
}
