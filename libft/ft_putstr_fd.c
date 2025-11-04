/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:21:04 by dbouizem          #+#    #+#             */
/*   Updated: 2024/12/22 07:20:57 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_putstr_fd - ecrit une chaîne de caractères sur un descripteur
** de fichier spécifié.
*/

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}
/*int	main()
{
	char *str = "Test";
	ft_putstr_fd(str, 1);
	return (0);
}*/
