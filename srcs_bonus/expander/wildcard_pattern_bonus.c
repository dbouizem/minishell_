/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_pattern_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:40:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/22 02:47:27 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minishell_bonus.h"

static void	init_build(t_wild_build *build, char *pattern, char *mask)
{
	ft_bzero(&build->state, sizeof(t_state));
	build->pattern = pattern;
	build->mask = mask;
	build->i = 0;
	build->j = 0;
	build->has_wc = 0;
}

static void	store_char(t_wild_build *build, char c)
{
	build->pattern[build->j] = c;
	build->mask[build->j] = '0';
	if (c == '*' && !build->state.in_single && !build->state.in_double)
	{
		build->mask[build->j] = '1';
		build->has_wc = 1;
	}
	build->j++;
}

static void	fill_pattern(t_wild_build *build, const char *arg)
{
	while (arg[build->i])
	{
		if (handle_quotes_flags(arg[build->i], &build->state))
			build->i++;
		else
			store_char(build, arg[build->i++]);
	}
}

int	build_pattern_mask_bonus(const char *arg, char **pattern,
			char **mask, int *has_wc)
{
	t_wild_build	build;

	*pattern = malloc(ft_strlen(arg) + 1);
	*mask = malloc(ft_strlen(arg) + 1);
	if (!*pattern || !*mask)
	{
		free(*pattern);
		free(*mask);
		return (0);
	}
	init_build(&build, *pattern, *mask);
	fill_pattern(&build, arg);
	build.pattern[build.j] = '\0';
	build.mask[build.j] = '\0';
	*has_wc = build.has_wc;
	if (!build.has_wc)
	{
		free(*pattern);
		*pattern = ft_strdup(arg);
		if (!*pattern)
			return (free(*mask), 0);
	}
	return (1);
}

int	wildcard_match_bonus(const char *pattern, const char *mask,
			const char *name)
{
	if (!*pattern)
		return (!*name);
	if (*pattern == '*' && *mask == '1')
	{
		if (wildcard_match_bonus(pattern + 1, mask + 1, name))
			return (1);
		if (*name)
			return (wildcard_match_bonus(pattern, mask, name + 1));
		return (0);
	}
	if (!*name || *pattern != *name)
		return (0);
	return (wildcard_match_bonus(pattern + 1, mask + 1, name + 1));
}
