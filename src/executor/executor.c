#include "../includes/minishell.h"

/* int	execute(t_cmd *cmd, t_shell *shell)
{
	int	exit_status;

	if (!cmd)
	{
		shell->exit_status = 1;  // ← ajout du point-virgule manquant
		return (1);
	}

	// Étape 1: Expansion des variables
	expand_commands(cmd, shell);

	// Étape 2: Supprimer les quotes
	remove_quotes_from_command(cmd);

	// Étape 3: Exécuter (pipeline ou commande simple)
	if (cmd->next)
		exit_status = execute_pipeline(cmd, shell);
	else
		exit_status = execute_command(cmd, shell);

	// Mettre à jour le code de sortie global
	shell->exit_status = exit_status;

	return (exit_status);
} */

int	execute(t_cmd *cmd, t_shell *shell)
{
	int	exit_status;

	print_pipeline(cmd);
	if (!cmd)
		return (1);
	expand_commands(cmd, shell);
	debug_executor(cmd, shell, "AFTER EXPANSION");
	remove_quotes_from_command(cmd);
	debug_executor(cmd, shell, "AFTER QUOTE REMOVAL");
	if (cmd->next)
		exit_status = execute_pipeline(cmd, shell);
	else
		exit_status = execute_command(cmd, shell);
	shell->exit_status = exit_status;
	printf("Exit status: %d\n", exit_status);
	return (exit_status);
}

int	execute_command(t_cmd *cmd, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;
	int	exit_status;

	if (save_redirections(&saved_stdin, &saved_stdout) != 0)
	{
		shell->exit_status = 1;
		return (1);
	}
	if (setup_redirections(cmd) != 0)
	{
		shell->exit_status = 1;
		restore_redirections(saved_stdin, saved_stdout);
		return (1);
	}
	if (cmd->args && cmd->args[0])
	{
		if (is_builtin(cmd->args[0]))
			exit_status = execute_builtin(cmd, shell);
		else
			exit_status = execute_external(cmd, shell);
	}
	else
		exit_status = 0;
	shell->exit_status = exit_status;
	restore_redirections(saved_stdin, saved_stdout);
	return (exit_status);
}
