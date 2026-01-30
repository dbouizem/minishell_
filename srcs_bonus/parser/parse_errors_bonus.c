/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:25:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/30 16:25:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell_bonus.h"

static t_token	*next_non_space(t_token *token)
{
	while (token && token->type == SPACES)
		token = token->next;
	return (token);
}

static t_token	*adjust_paren_token(t_token *tok)
{
	t_token	*next;
	t_token	*next_next;

	if (!tok || tok->type != PAREN_OPEN)
		return (tok);
	next = next_non_space(tok->next);
	next_next = NULL;
	if (next)
		next_next = next_non_space(next->next);
	if (!(next && next->type == WORD
			&& next_next && next_next->type == PAREN_CLOSE))
		tok = next;
	return (tok);
}

static void	print_syntax_token(t_token *tok)
{
	if (tok && is_redir(tok->type))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putstr_fd(tok->value, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
	}
	else if (tok)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putstr_fd(tok->value, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
	}
	else
	{
		ft_putendl_fd(
			"minishell: syntax error near unexpected token `newline'",
			STDERR_FILENO);
	}
}

void	parse_syntax_error(t_token **tokens, t_shell *shell)
{
	t_token	*tok;

	tok = NULL;
	if (tokens)
		tok = *tokens;
	tok = adjust_paren_token(tok);
	print_syntax_token(tok);
	if (shell)
		shell->exit_status = 2;
}
