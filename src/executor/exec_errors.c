#include "../includes/minishell.h"

/* Gestion des erreurs d'exécution */
void	handle_exec_error(char *cmd, t_shell *shell)
{
	if (ft_strchr(cmd, '/'))
		handle_absolute_path_error(cmd, shell);
	else
		handle_command_not_found(cmd, shell);
}

/* Erreurs pour les chemins absolus */
void	handle_absolute_path_error(char *cmd, t_shell *shell)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		print_error_is_directory(cmd, shell, 126);
	else if (access(cmd, F_OK) != 0)
		print_error_no_such_file(cmd, shell, 127);
	else if (access(cmd, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
		shell->exit_status = 126;
	}
}

/* Commande non trouvée */
void	handle_command_not_found(char *cmd, t_shell *shell)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	shell->exit_status = 127;
}

/* Erreur "Is a directory" */
void	print_error_is_directory(char *cmd, t_shell *shell, int status)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": Is a directory", STDERR_FILENO);
	shell->exit_status = status;
}

/* Erreur "No such file or directory" */
void	print_error_no_such_file(char *cmd, t_shell *shell, int status)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	shell->exit_status = status;
}
