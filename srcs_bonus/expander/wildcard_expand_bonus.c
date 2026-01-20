/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expand_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:40:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/21 20:40:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "../../includes/minishell.h"
#include "../../includes/minishell_bonus.h"

static int	collect_cleanup(DIR *dir, char **matches, int ret)
{
	if (dir)
		closedir(dir);
	ft_free_tab(matches);
	return (ret);
}

static int	collect_matches(const char *pattern, const char *mask,
				char ***matches)
{
	DIR				*dir;
	struct dirent	*ent;
	int				match_count;

	dir = opendir(".");
	if (!dir)
		return (0);
	*matches = NULL;
	match_count = 0;
	ent = readdir(dir);
	while (ent)
	{
		if (ent->d_name[0] != '.'
			|| (pattern[0] == '.' && ent->d_name[1] != '\0'
				&& (ent->d_name[1] != '.' || ent->d_name[2] != '\0')))
			if (wildcard_match_bonus(pattern, mask, ent->d_name)
				&& !append_arg_bonus(matches, &match_count,
					ft_strdup(ent->d_name)))
				return (collect_cleanup(dir, *matches, -1));
		ent = readdir(dir);
	}
	closedir(dir);
	if (match_count == 0)
		return (collect_cleanup(NULL, *matches, 0));
	return (match_count);
}

static int	expand_arg(char *arg, char ***dst, int *count)
{
	char	*pattern;
	char	*mask;
	char	**matches;
	int		has_wc;
	int		match_count;

	if (!build_pattern_mask_bonus(arg, &pattern, &mask, &has_wc))
		return (0);
	if (!has_wc)
		return (append_literal_bonus(dst, count, pattern, mask));
	match_count = collect_matches(pattern, mask, &matches);
	free(mask);
	if (match_count < 0)
	{
		free(pattern);
		return (0);
	}
	if (match_count == 0)
		return (append_arg_bonus(dst, count, pattern));
	sort_strings_bonus(matches, match_count);
	free(pattern);
	return (append_array_bonus(dst, count, matches, match_count));
}

static int	expand_cmd_args(t_cmd *cmd)
{
	char	**new_args;
	int		i;
	int		count;

	new_args = NULL;
	i = 0;
	count = 0;
	while (cmd->args[i])
	{
		if (!expand_arg(cmd->args[i], &new_args, &count))
		{
			ft_free_tab(new_args);
			return (0);
		}
		i++;
	}
	ft_free_tab(cmd->args);
	cmd->args = new_args;
	return (1);
}

void	expand_wildcards(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->args && cmd->args[0])
			expand_cmd_args(cmd);
		cmd = cmd->next;
	}
}
