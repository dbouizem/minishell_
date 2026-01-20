/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:42:00 by dbouizem          #+#    #+#             */
/*   Updated: 2025/12/08 18:42:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	cleanup_parsed(t_cmd *cmds, t_token *tokens, t_shell *shell)
{
	if (cmds)
		free_cmd(cmds);
	shell->current_cmds = NULL;
	free_tokens(tokens);
	shell->current_tokens = NULL;
}

static int	execute_parsed(t_token *tokens, t_shell *shell)
{
	t_cmd	*cmds;

	shell->current_tokens = tokens;
	cmds = parse(tokens, shell);
	if (!cmds)
	{
		cleanup_parsed(NULL, tokens, shell);
		return (0);
	}
	shell->current_cmds = cmds;
	execute(cmds, shell);
	cleanup_parsed(cmds, tokens, shell);
	return (0);
}

int	process_input(char *input, t_shell *shell)
{
	t_token	*tokens;

	if (!prepare_tokens(input, shell, &tokens))
		return (0);
	return (execute_parsed(tokens, shell));
}
