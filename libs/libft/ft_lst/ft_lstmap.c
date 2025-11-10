/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:18:41 by dvavryn           #+#    #+#             */
/*   Updated: 2025/05/18 01:01:34 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_out;
	t_list	*node_out;
	void	*buf;

	if (lst == NULL || f == NULL)
		return (NULL);
	lst_out = NULL;
	while (lst != NULL)
	{
		buf = f(lst->content);
		node_out = ft_lstnew(buf);
		if (!node_out)
		{
			del(buf);
			ft_lstclear(&lst_out, del);
			return (NULL);
		}
		ft_lstadd_back(&lst_out, node_out);
		lst = lst->next;
	}
	return (lst_out);
}
