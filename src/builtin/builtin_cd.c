#include "../../includes/minishell.h"

static void	update_pwd(char *old_pwd, t_shell *shell)
{
	char	cwd[2048];

	if (old_pwd && old_pwd[0])
		update_env_var("OLDPWD", old_pwd, shell);
	if (getcwd(cwd, sizeof(cwd)))
		update_env_var("PWD", cwd, shell);
}

static int	cd_home(t_shell *shell, char *old_pwd)
{
	char	*home;

	home = get_env_value("HOME", shell);
	if (!home)
		return (ft_putendl_fd("minishell: cd: HOME not set", 2), 1);
	if (chdir(home) == -1)
		return (perror("minishell: cd"), 1);
	update_pwd(old_pwd, shell);
	return (0);
}

static int	cd_empty_path(char **args)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("No such file or directory", 2);
	return (1);
}

static int	cd_to_oldpwd(t_shell *shell, char *old_pwd)
{
	char	*oldpwd_env;

	oldpwd_env = get_env_value("OLDPWD", shell);
	if (!oldpwd_env || !oldpwd_env[0])
		return (ft_putendl_fd("minishell: cd: OLDPWD not set", 2), 1);
	ft_putendl_fd(oldpwd_env, 1);
	if (chdir(oldpwd_env) == -1)
		return (perror("minishell: cd"), 1);
	update_pwd(old_pwd, shell);
	return (0);
}

int	builtin_cd(char **args, t_shell *shell)
{
	char	old_pwd[2048];

	if (!getcwd(old_pwd, sizeof(old_pwd)))
		old_pwd[0] = '\0';
	if (!args[1])
		return (cd_home(shell, old_pwd));
	if (args[1][0] == '\0')
		return (cd_empty_path(args));
	if (args[2])
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	if (ft_strcmp(args[1], "-") == 0)
		return (cd_to_oldpwd(shell, old_pwd));
	if (chdir(args[1]) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	update_pwd(old_pwd, shell);
	return (0);
}
