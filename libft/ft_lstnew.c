/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 07:12:40 by dbouizem          #+#    #+#             */
/*   Updated: 2025/01/11 10:23:49 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_lstnew - crée un nouveau nœud pour une liste chaînée.
*/

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
/*
int	main()
{
	int	v1 = 25, v2 = 42, v3 = 99;
	t_list	*n1 = ft_lstnew(&v1);
	t_list	*n2 = ft_lstnew(&v2);
	t_list	*n3 = ft_lstnew(&v3);

	n1->next = n2;
	n2->next = n3;

	t_list	*current;
	current = n1;
	while (current != NULL)
	{
		printf("The content node is: %d\n", *(int *)(current->content));
		current = current->next;
	}
	free(n1);
	free(n2);
	free(n3);
	return (0);
}*/
