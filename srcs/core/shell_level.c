/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 04:15:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/28 04:15:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_numeric_str(const char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static int	compute_shlvl(const char *value)
{
	long long	level;
	int			overflow;

	if (!is_numeric_str(value))
		return (1);
	level = ft_atoll(value, &overflow);
	if (overflow || level < 0 || level >= 1000)
		return (1);
	return ((int)(level + 1));
}

void	update_shell_level(t_shell *shell)
{
	char	*value;
	char	*level_str;
	int		level;

	if (!shell)
		return ;
	value = get_env_value("SHLVL", shell);
	level = compute_shlvl(value);
	level_str = ft_itoa(level);
	if (!level_str)
		return ;
	update_env_var("SHLVL", level_str, shell);
	free(level_str);
}
