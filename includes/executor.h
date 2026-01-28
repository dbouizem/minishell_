/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:53:39 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/28 16:53:40 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <signal.h>
# include <sys/types.h>
# include <termios.h>

typedef struct s_cmd	t_cmd;
typedef struct s_shell	t_shell;
typedef struct s_redir	t_redir;

# define PATH_ERR_NONE 0
# define PATH_ERR_PERM 1
# define PATH_ERR_ISDIR 2

typedef struct s_pipeline_data
{
	t_cmd	*cmd;
	t_shell	*shell;
	int		**pipes;
	pid_t	*pids;
	int		num_pipes;
	int		num_commands;
}	t_pipeline_data;

typedef struct s_path_search
{
	const char	*path;
	char		*cmd;
	int			*path_error;
}	t_path_search;

typedef struct s_heredoc_params
{
	int		fd;
	char	*delimiter;
	int		expand;
	t_shell	*shell;
}	t_heredoc_params;

typedef struct s_heredoc_ctx
{
	char				tmp_filename[64];
	int					fd;
	int					status;
	int					expand;
	struct sigaction	old_int;
	struct sigaction	old_quit;
	t_heredoc_params	params;
}	t_heredoc_ctx;

int		execute(t_cmd *cmd, t_shell *shell);
int		execute_command(t_cmd *cmd, t_shell *shell);
void	execute_command_child(t_cmd *cmd, t_shell *shell);
void	cleanup_child_pipes(int **pipes, int num_pipes, int cmd_index);

int		execute_pipeline(t_cmd *cmd, t_shell *shell);
int		prepare_pipeline_heredocs(t_cmd *cmd, t_shell *shell);
void	close_pipeline_heredocs(t_cmd *cmd);
int		**create_pipes(int num_pipes);
int		fork_all_commands(t_pipeline_data *data);
int		wait_all_children(pid_t *pids, int num_commands, t_shell *shell);
void	close_all_pipes(int **pipes, int num_pipes);
void	cleanup_pipeline_resources(t_pipeline_data *data);

int		execute_external(t_cmd *cmd, t_shell *shell);
void	execute_external_no_fork(t_cmd *cmd, t_shell *shell);
char	*search_in_paths(const char *path, char *cmd, int *path_error);
char	*handle_absolute_path(char *cmd);

int		setup_redirections(t_cmd *cmd, t_shell *shell);
int		save_redirections(int *saved_stdin, int *saved_stdout);
int		restore_redirections(int saved_stdin, int saved_stdout);
int		handle_heredoc_redirection(t_redir *redir, t_shell *shell);
void	reset_heredoc_fd(t_redir *redir);
int		abort_heredoc(int fd, char *tmp_filename, int status);
int		finalize_heredoc_fd(int fd, char *tmp_filename, t_redir *redir);
int		open_heredoc_tmp(char *path, size_t size);
char	*read_heredoc_line(t_shell *shell);
char	*expand_heredoc_line(char *line, t_shell *shell);
int		write_heredoc_content(t_heredoc_params *params);

void	setup_heredoc_signals(struct sigaction *old_int,
			struct sigaction *old_quit);
void	heredoc_sigint_handler(int signo);
void	restore_signals(struct sigaction *old_int,
			struct sigaction *old_quit);
char	*remove_quote(char *str);

void	handle_exec_error(char *cmd, t_shell *shell);
void	handle_absolute_path_error(char *cmd, t_shell *shell);
void	handle_command_not_found(char *cmd, t_shell *shell);
void	print_error_is_directory(char *cmd, t_shell *shell, int status);
void	print_error_no_such_file(char *cmd, t_shell *shell, int status);

void	handle_execve_error(char *cmd_path, t_shell *shell);
void	exit_child(int status, t_shell *shell);
int		handle_file_error(char *filename);
int		handle_dup2_error(int fd);
int		handle_malloc_error(void);
int		handle_pipe_error(void);
int		handle_input_redirection(t_redir *redir);
int		handle_output_redirection(t_redir *redir, t_redir_type type);

void	free_string_array(char **array);
pid_t	fork_process(void);
void	wait_for_child(pid_t pid, int *status, t_shell *shell);
void	report_signal_status(int sig, int status, t_shell *shell,
			int *printed);

#endif
