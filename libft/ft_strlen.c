/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:18:03 by dbouizem          #+#    #+#             */
/*   Updated: 2024/12/24 23:14:14 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_strlen - calcule la longueur d'une chaîne de caractères.
*/

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}
/*
int	main()
{
	char	*str = "---Testting ft_strlen---";
	size_t	result = ft_strlen(str);
	printf("The length of str: %zu\n", result);
	return (0);
}*/
