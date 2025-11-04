/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:45:31 by dbouizem          #+#    #+#             */
/*   Updated: 2024/12/22 07:31:13 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_bzero - remplie une zone mémoire avec des zéros.
**
** Compilation: gcc -Wall -Wextra -Werror ft_strlen.c ft_strlcpy.c ft_bzero.c
*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*cs;

	cs = (unsigned char *) s;
	while (n--)
		*cs++ = '\0';
}
/*
int	main()
{
	char *str = malloc(20 * sizeof(char));
	if (str == NULL)
	{
		printf("Error");
		return (1);
	}
	ft_strlcpy(str, "Hi Memo", 20);
	printf("Before ft_bzero: %s\n", str);
	ft_bzero(str, 20);
	printf("After ft_bzero: %s\n", str);
	free(str);
	return (0);
}*/
