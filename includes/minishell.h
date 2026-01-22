/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:40:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/21 05:06:13 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <readline/rlconf.h>
# include <readline/rltypedefs.h>
# include <unistd.h>
# include <termios.h>
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>

# include "libft.h"
# include "colors.h"
# include "token.h"
# include "parser.h"
# include "expander.h"
# include "executor.h"
# include "builtin.h"
# include "env.h"

extern volatile sig_atomic_t	g_signal;

typedef struct s_ast	t_ast;

typedef struct s_shell
{
	char			**env;
	t_env			*env_list;
	t_token			*current_tokens;
	t_cmd			*current_cmds;
	t_ast			*current_ast;
	void			(*free_ast)(t_ast *ast);
	char			*current_input;
	int				exit_status;
	int				should_exit;
	int				interactive;
	struct termios	original_term;
	int				num_pipes;
}	t_shell;

void	init_shell(t_shell *shell, char **envp);
void	cleanup_shell(t_shell *shell);
void	cleanup_shell_child(t_shell *shell);

void	setup_signals(void);
void	setup_child_signals(void);

char	*read_input(void);
char	*read_input_non_interactive(void);
int		process_input(char *input, t_shell *shell);

void	shell_error(t_shell *shell, char *message, int exit_code);
void	process_error(char *context, t_shell *shell);
void	*check_malloc(void *ptr, char *context);

#endif
