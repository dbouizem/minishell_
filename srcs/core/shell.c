/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:40:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/31 16:14:45 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_shell(t_shell *shell, char **envp)
{
	ft_memset(shell, 0, sizeof(t_shell));
	shell->exit_status = 0;
	shell->env = NULL;
	shell->env_list = NULL;
	shell->interactive = (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));
	if (shell->interactive)
	{
		rl_catch_signals = 0;
		rl_catch_sigwinch = 0;
		if (tcgetattr(STDIN_FILENO, &shell->original_term) == -1)
		{
			shell->interactive = 0;
			shell_error(shell, "tcgetattr", 1);
		}
	}
	shell->env_list = env_array_to_list(envp);
	if (!shell->env_list && envp && *envp)
		shell_error(shell, "Failed to initialize environment list", 1);
	env_list_to_array(shell);
	if (envp && *envp)
		update_shell_level(shell);
}

void	cleanup_shell(t_shell *shell)
{
	int	i;

	if (shell->interactive
		&& tcsetattr(STDIN_FILENO, TCSANOW, &shell->original_term) == -1)
		perror("minishell: tcsetattr");
	if (shell->env)
	{
		i = 0;
		while (shell->env[i])
			free(shell->env[i++]);
		free(shell->env);
		shell->env = NULL;
	}
	if (shell->env_list)
	{
		free_env_list(shell->env_list);
		shell->env_list = NULL;
	}
	ft_gnl_clear();
	rl_clear_history();
}

static void	cleanup_shell_runtime(t_shell *shell)
{
	if (shell->current_tokens)
	{
		free_tokens(shell->current_tokens);
		shell->current_tokens = NULL;
	}
	if (shell->current_input)
	{
		free(shell->current_input);
		shell->current_input = NULL;
	}
	if (shell->free_ast && shell->current_ast)
	{
		shell->free_ast(shell->current_ast);
		shell->current_ast = NULL;
	}
	else if (shell->current_cmds)
	{
		free_cmd(shell->current_cmds);
		shell->current_cmds = NULL;
	}
}

static void	cleanup_shell_env(t_shell *shell)
{
	int	i;

	if (shell->env)
	{
		i = 0;
		while (shell->env[i])
			free(shell->env[i++]);
		free(shell->env);
		shell->env = NULL;
	}
	if (shell->env_list)
	{
		free_env_list(shell->env_list);
		shell->env_list = NULL;
	}
}

void	cleanup_shell_child(t_shell *shell)
{
	if (!shell)
		return ;
	cleanup_shell_runtime(shell);
	cleanup_shell_env(shell);
	rl_clear_history();
}
