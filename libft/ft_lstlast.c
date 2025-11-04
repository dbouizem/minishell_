/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 07:25:53 by dbouizem          #+#    #+#             */
/*   Updated: 2025/01/11 11:23:48 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_lstlast - retourne le dernier élément d'une liste chaînée.
*/

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
/*int	main()
{
	t_list	*n1 = ft_lstnew("P");
	t_list	*n2 = ft_lstnew("D");
	t_list	*n3 = ft_lstnew("T");
	t_list	*last;

	if (!n1 || !n2 || !n3)
	{
		printf("Error");
		ft_lstclear(&n1, free);
		return (1);
	}

	n1->next = n2;
	n2->next = n3;

	last = ft_lstlast(n1);
	printf("Last element : %s\n", (char *)last->content);

	ft_lstclear(&n1, free);
	return (0);
}*/
