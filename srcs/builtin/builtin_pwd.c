/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:54:20 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/28 16:54:21 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*getcwd_dynamic(void)
{
	size_t	size;
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf)
		return (buf);
	size = 128;
	while (1)
	{
		buf = malloc(size);
		if (!buf)
			return (NULL);
		if (getcwd(buf, size))
			return (buf);
		free(buf);
		if (errno != ERANGE)
			return (NULL);
		size *= 2;
	}
}

int	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd_dynamic();
	if (cwd)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		free(cwd);
		return (0);
	}
	else
	{
		perror("minishell: pwd");
		return (1);
	}
}
