/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors_bonus_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:34:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/30 16:34:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell_bonus.h"

void	pipe_syntax_error(t_shell *shell)
{
	ft_putendl_fd("minishell: syntax error near unexpected token `|'",
		STDERR_FILENO);
	if (shell)
		shell->exit_status = 2;
}

void	redir_syntax_error(t_shell *shell)
{
	ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
		STDERR_FILENO);
	if (shell)
		shell->exit_status = 2;
}

int	parse_memory_error(char *context)
{
	ft_putstr_fd("minishell: parse error: memory allocation failed for ",
		STDERR_FILENO);
	ft_putendl_fd(context, STDERR_FILENO);
	return (0);
}
