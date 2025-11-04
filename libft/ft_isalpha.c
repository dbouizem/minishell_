/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:09:25 by dbouizem          #+#    #+#             */
/*   Updated: 2024/12/22 07:28:51 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_isalpha - test des caractères alphabétiques.
*/

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
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
		if (ft_isalpha(c))
		{
			ft_putstr_fd("OK for: ", 1);
			ft_putchar_fd(c, 1);
			ft_putchar_fd('\n', 1);
		}
		else
		{
			ft_putstr_fd("Not ALPHA for: ", 1);
			ft_putchar_fd(c, 1);
			ft_putchar_fd('\n', 1);
		}
		c++;
	}
	return (0);
}*/
