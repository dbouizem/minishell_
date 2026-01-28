/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:54:37 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/28 16:54:38 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	shell_error(t_shell *shell, char *message, int exit_code)
{
	ft_putstr_fd("minishell: error: ", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	if (shell)
		cleanup_shell(shell);
	exit(exit_code);
}

void	process_error(char *context, t_shell *shell)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(context, STDERR_FILENO);
	if (shell)
		shell->exit_status = 1;
}

void	*check_malloc(void *ptr, char *context)
{
	if (!ptr)
	{
		ft_putstr_fd("minishell: memory allocation failed for ", STDERR_FILENO);
		ft_putendl_fd(context, STDERR_FILENO);
		return (NULL);
	}
	return (ptr);
}
