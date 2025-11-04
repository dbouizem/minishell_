/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 07:24:57 by dbouizem          #+#    #+#             */
/*   Updated: 2025/01/11 11:28:34 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_lstsize - compte le nombre d'éléments dans une liste chaînée.
*/

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}
/*
int	main()
{
	t_list	*lst = NULL;
	printf("Size of lst is: %d\n\n", ft_lstsize(lst));

	t_list	*n1 = ft_lstnew("A");
	t_list	*n2 = ft_lstnew("B");
	t_list	*n3 = ft_lstnew("C");

	n1->next = n2;
	n2->next = n3;

	lst = n1;
	printf("Size of lst is: %d\n", ft_lstsize(lst));
	ft_lstclear(&lst, free);
	return(0);
}*/
