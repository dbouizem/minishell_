/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 01:19:14 by dbouizem          #+#    #+#             */
/*   Updated: 2025/01/11 03:47:38 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_lstiter - itère sur chaque élément d'une liste chaînée et applique
** une fonction donnée au contenu de chaque nœud.
*/

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
void	print_content(void *content)
{
	printf("%s\n", (char *)content);
}

int	main(void)
{
	t_list	*lst;
	t_list	*n1 = ft_lstnew(ft_strdup("First noeud"));
	t_list	*n2 = ft_lstnew(ft_strdup("Second noeud"));
	t_list	*n3 = ft_lstnew(ft_strdup("Third noeud"));

	if (!n1 || !n2 || !n3)
		printf("Error: memory allocation failed");

	n1->next = n2;
	n2->next = n3;
	n3->next = NULL;

	lst = n1;
	ft_lstiter(lst, print_content);
	ft_lstclear(&lst, free);
	return (0);
}*/
