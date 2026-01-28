/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:56:09 by fadwa             #+#    #+#             */
/*   Updated: 2026/01/28 16:56:10 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

pid_t	fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	return (pid);
}

void	handle_execve_error(char *cmd_path, t_shell *shell)
{
	int	err;

	err = errno;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd_path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(err), STDERR_FILENO);
	free(cmd_path);
	if (err == ENOENT)
		exit_child(127, shell);
	exit_child(126, shell);
}

int	handle_pipe_error(void)
{
	perror("pipe");
	return (1);
}

void	exit_child(int status, t_shell *shell)
{
	cleanup_shell_child(shell);
	exit(status);
}
