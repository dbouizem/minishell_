/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 07:29:48 by dbouizem          #+#    #+#             */
/*   Updated: 2025/01/11 01:23:48 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_lstclear - supprime et libère la mémoire de tous les éléments
** (noeuds) d'une liste chaînée.
*/

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del) (void *))
{
	t_list	*temp;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
/*
void	del(void *content)
{
	free(content);
}

int	main(void)
{
	t_list	*lst;
	t_list	*current;
	t_list	*n1 = ft_lstnew(ft_strdup("First noeud"));
	t_list	*n2 = ft_lstnew(ft_strdup("Second noeud"));
	t_list	*n3 = ft_lstnew(ft_strdup("Third noeud"));

	if (!n1 || !n2 || !n3)
		printf("Error: memory allocation failed");

	n1->next = n2;
	n2->next = n3;
	n3->next = NULL;

	lst = n1;
	current = lst;
	printf("lst Before Clear: ");
	while (current)
	{
		printf(" [%s] ", (char *)(current->content));
		current = current->next;
	}
	ft_lstclear(&lst, del);
	if (lst == NULL)
		printf("\nlst now is [NULL] After clean\n");
	return (0);
}*/
