/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:32:49 by dbouizem          #+#    #+#             */
/*   Updated: 2024/12/22 07:28:34 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_isascii - test du caractère ASCII.
*/

#include "libft.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
/*
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *str, int fd)
{
	while (*str)
		write(fd, str++, 1);
}

int	main()
{
	int	c;

	c = -5;
	while (c <= 135)
	{
		if (ft_isascii(c))
		{
			ft_putstr_fd("OK for: ", 1);
			ft_putchar_fd(c, 1);
			ft_putchar_fd('\n', 1);
		}
		else
		{
			ft_putstr_fd("Not ASCII for: ", 1);
			ft_putchar_fd(c, 1);
			ft_putchar_fd('\n', 1);
		}
		c++;
	}
	return (0);
}*/
