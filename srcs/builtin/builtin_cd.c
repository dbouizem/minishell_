#include "../../includes/minishell.h"

static char	*get_oldpwd_dynamic(void)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		old_pwd = ft_strdup("");
	return (old_pwd);
}

static void	update_pwd(char *old_pwd, t_shell *shell)
{
	char	*cwd;

	if (old_pwd && old_pwd[0])
		update_env_var("OLDPWD", old_pwd, shell);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		update_env_var("PWD", cwd, shell);
		free(cwd);
	}
}

static int	handle_no_args(t_shell *shell, char *old_pwd)
{
	char	*home;

	home = get_env_value("HOME", shell);
	if (!home)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		free(old_pwd);
		return (1);
	}
	if (home[0] == '\0')
	{
		free(old_pwd);
		return (0);
	}
	if (chdir(home) == -1)
	{
		perror("minishell: cd");
		free(old_pwd);
		return (1);
	}
	update_pwd(old_pwd, shell);
	free(old_pwd);
	return (0);
}

static int	handle_dash_arg(t_shell *shell, char *old_pwd)
{
	char	*oldpwd_env;

	oldpwd_env = get_env_value("OLDPWD", shell);
	if (!oldpwd_env || !oldpwd_env[0])
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		free(old_pwd);
		return (1);
	}
	ft_putendl_fd(oldpwd_env, 1);
	if (chdir(oldpwd_env) == -1)
	{
		perror("minishell: cd");
		free(old_pwd);
		return (1);
	}
	update_pwd(old_pwd, shell);
	free(old_pwd);
	return (0);
}

int	builtin_cd(char **args, t_shell *shell)
{
	char	*old_pwd;

	old_pwd = get_oldpwd_dynamic();
	if (!args[1])
		return (handle_no_args(shell, old_pwd));
	if (args[1][0] == '\0')
		return (print_cd_error(args[1], "No such file or directory"),
			free(old_pwd), 1);
	if (args[2])
		return (print_cd_error(NULL, "too many arguments"),
			free(old_pwd), 1);
	if (ft_strcmp(args[1], "-") == 0)
		return (handle_dash_arg(shell, old_pwd));
	if (chdir(args[1]) == -1)
		return (print_cd_error(args[1], strerror(errno)),
			free(old_pwd), 1);
	update_pwd(old_pwd, shell);
	return (free(old_pwd), 0);
}
