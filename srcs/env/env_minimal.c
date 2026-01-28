/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_minimal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:55:05 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/28 16:55:06 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_pwd_value(void)
{
	char	buffer[PATH_MAX];

	if (getcwd(buffer, sizeof(buffer)))
		return (ft_strdup(buffer));
	return (ft_strdup("/"));
}

void	init_minimal_env(t_shell *shell, char *argv0)
{
	char	*pwd;

	if (!shell)
		return ;
	pwd = get_pwd_value();
	if (pwd)
	{
		set_env_value("PWD", pwd, shell);
		free(pwd);
	}
	set_env_value("SHLVL", "1", shell);
	if (argv0 && *argv0)
		set_env_value("_", argv0, shell);
	else
		set_env_value("_", "minishell", shell);
}
