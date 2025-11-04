/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:58:48 by dbouizem          #+#    #+#             */
/*   Updated: 2024/12/22 07:21:53 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_putendl_fd - ecrit une chaîne de caractères suivie d'un saut de ligne
** sur un descripteur de fichier spécifié.
*/

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
}
/*int	main()
{
	ft_putendl_fd("ABCD", 1);
	ft_putendl_fd("Error message!", 2);
	return (0);
}*/
