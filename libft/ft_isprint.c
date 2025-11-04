/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:09:15 by dbouizem          #+#    #+#             */
/*   Updated: 2024/12/22 07:28:09 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_isprint - test printing character (caractère d'espace inclus).
*/

#include "libft.h"

int	ft_isprint(int c)
{
	return ((c > 31 && c < 127));
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

	c = 0;
	while (c <= 127)
	{
		if (ft_isprint(c))
		{
			ft_putstr_fd("OK for: ", 1);
			ft_putchar_fd(c, 1);
			ft_putchar_fd('\n', 1);
		}
		else
		{
			ft_putstr_fd("Not PRINT for: ", 1);
			ft_putchar_fd(c, 1);
			ft_putchar_fd('\n', 1);
		}
		c++;
		}
	return (0);
}*/
