/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:58:06 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/28 16:58:07 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_syntax_error(t_token **tokens, t_shell *shell)
{
	if (*tokens && is_redir((*tokens)->type))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putstr_fd((*tokens)->value, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
	}
	else if (*tokens)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putstr_fd((*tokens)->value, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
	}
	else
	{
		ft_putendl_fd(
			"minishell: syntax error near unexpected token `newline'",
			STDERR_FILENO);
	}
	shell->exit_status = 2;
}

void	pipe_syntax_error(t_shell *shell)
{
	ft_putendl_fd("minishell: syntax error near unexpected token `|'",
		STDERR_FILENO);
	shell->exit_status = 2;
}

void	redir_syntax_error(t_shell *shell)
{
	ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
		STDERR_FILENO);
	shell->exit_status = 2;
}

int	parse_memory_error(char *context)
{
	ft_putstr_fd("minishell: parse error: memory allocation failed for ",
		STDERR_FILENO);
	ft_putendl_fd(context, STDERR_FILENO);
	return (0);
}
