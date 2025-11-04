/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:47:35 by dbouizem          #+#    #+#             */
/*   Updated: 2025/04/25 03:31:23 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_striteri - applique une fonction donnée à chaque caractère d'une chaîne.
** La fonction `f` prend deux arguments :
** - L'index du caractère actuel (unsigned int)
** - Un pointeur vers le caractère actuel (char *)
** Modifie la chaîne d’origine
**
** Compilation: gcc -Wall -Wextra -Werror ft_striteri.c ft_tolower.c
*/

#include "libft.h"

/*void	apply_tolower(unsigned int i, char *c)
{
	(void)i;
	if (c && *c)
		*c = ft_tolower(*c);
}*/

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (*s)
	{
		f(i, s);
		i++;
		s++;
	}
}
/*
int	main()
{
	char	str[] = "ABCD";
	printf("Original: %s\n", str);
	ft_striteri(str, apply_tolower);
	printf("Char: %s\n", str);
	return (0);
}*/
