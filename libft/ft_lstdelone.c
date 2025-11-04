/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 07:28:40 by dbouizem          #+#    #+#             */
/*   Updated: 2025/01/11 11:15:18 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_lstdelone - supprimer un élément de liste chaînée.
*/

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
/*
void	del(void *content)
{
	free(content);
}

int	main(void)
{
	t_list	*lst;

	lst = ft_lstnew(ft_strdup("Testing my code"));
	printf("lst before deletion: %s\n", (char *)(lst->content));
	if (!lst)
	{
		printf("Error");
		return (1);
	}
	//ft_lstdelone(lst, free);
	ft_lstdelone(lst, del);
	ft_lstclear(&lst, free);
	return (0);
}*/
