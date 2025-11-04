/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 03:49:55 by dbouizem          #+#    #+#             */
/*   Updated: 2025/01/11 11:05:43 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_lstmap - applique une fonction à chaque élément d'une liste chaînée
** pour créer une nouvelle liste.
*/

#include "libft.h"

/*static void	*ft_upper(void *content)
{
	char	*str = (char *)content;
	char	*upper = ft_strdup(str);
	int		i = 0;

	if (!upper)
		return (NULL);
	while (upper[i])
	{
		upper[i] = ft_toupper(upper[i]);
		i++;
	}
	return ((void *)upper);
}

static void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
}
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_noeud;
	void	*new_content;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		new_noeud = ft_lstnew(new_content);
		if (!new_noeud)
		{
			if (new_content)
				del(new_content);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_noeud);
		lst = lst->next;
	}
	return (new_lst);
}
/*
int	main()
{
	t_list	*lst;
	t_list	*n1 = ft_lstnew(ft_strdup("I Testing "));
	t_list	*n2 = ft_lstnew(ft_strdup("My "));
	t_list	*n3 = ft_lstnew(ft_strdup("Code."));
	t_list	*n_lst;

	if (!n1 || !n2 || !n3)
	{
		printf("Error: allocation momry failed");
		return (1);
	}
	n1->next = n2;
	n2->next = n3;
	n3->next = NULL;
	lst = n1;

	printf("lst Before mapping: \n");
	print_list(lst);

	n_lst = ft_lstmap(lst, ft_upper, free);

	printf("\nlst After mapping: \n");
	print_list(n_lst);

	ft_lstclear(&lst, free);
	ft_lstclear(&n_lst, free);
	return (0);
}*/
