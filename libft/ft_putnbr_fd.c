/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 05:47:55 by dbouizem          #+#    #+#             */
/*   Updated: 2024/12/22 07:21:21 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_putnbr_fd - ecrit un entier sur le file descriptor spécifié.
**
** Compilation: gcc -Wall -Wextra -Werror ft_putnbr_fd.c ft_putchar_fd.c
** ft_atoi.c ft_putstr_fd.c
** ./out.a 122324
** cat output.txt
*/
//#include <fcntl.h>
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nbr;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = (unsigned int)(n * -1);
	}
	else
		nbr = (unsigned int)n;
	if (nbr >= 10)
	{
		ft_putnbr_fd(nbr / 10, fd);
	}
	ft_putchar_fd((char)(nbr % 10 + '0'), fd);
}
/*
int	main(int ac, char **av)
{
	int	number;
	int	fd;

	if (ac != 2)
	{
		if (ac < 2)
			ft_putstr_fd("File name missing.\n", 2);
		else
			ft_putstr_fd("Too many arguments.\n", 2);
		return (1);
	}
	number = ft_atoi(av[1]);
	if (number == 0 && av[1][0] != '0')
	{
		ft_putstr_fd("Invalid number format.\n", 2);
		return (1);
	}
	fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Could not create output file.\n", 2);
		return (1);
	}
	ft_putnbr_fd(number, fd);
	close(fd);
	return (0);
}*/
