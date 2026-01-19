/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:18:00 by dbouizem          #+#    #+#             */
/*   Updated: 2025/12/08 18:18:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell_bonus.h"

static int	is_only_whitespace(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

static int	prepare_tokens(char *input, t_shell *shell, t_token **tokens)
{
	if (!input || input[0] == '\0' || is_only_whitespace(input))
		return (0);
	*tokens = tokenize(input);
	if (!*tokens)
	{
		shell->exit_status = 2;
		return (0);
	}
	return (1);
}

static void	cleanup_bonus_ast(t_ast *ast, t_token *tokens, t_shell *shell)
{
	if (ast)
		free_ast_bonus(ast);
	shell->current_ast = NULL;
	shell->free_ast = NULL;
	free_tokens(tokens);
	shell->current_tokens = NULL;
}

static int	execute_bonus_ast(t_token *tokens, t_shell *shell)
{
	t_ast	*ast;

	shell->current_tokens = tokens;
	ast = parse_ast_bonus(tokens, shell);
	if (!ast)
	{
		free_tokens(tokens);
		shell->current_tokens = NULL;
		return (0);
	}
	shell->current_ast = ast;
	shell->free_ast = free_ast_bonus;
	shell->current_cmds = NULL;
	execute_ast_bonus(ast, shell);
	cleanup_bonus_ast(ast, tokens, shell);
	return (0);
}

int	process_input(char *input, t_shell *shell)
{
	t_token	*tokens;

	if (!prepare_tokens(input, shell, &tokens))
		return (0);
	return (execute_bonus_ast(tokens, shell));
}
