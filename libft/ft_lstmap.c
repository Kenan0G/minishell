/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:32:12 by jsabound          #+#    #+#             */
/*   Updated: 2022/11/16 19:35:06 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*temp;

	temp = ft_lstnew(f(lst->content));
	if (!temp)
	{
		ft_lstclear(&lst, del);
		return (NULL);
	}
	res = temp;
	lst = lst->next;
	while (lst)
	{
		temp = ft_lstnew(f(lst->content));
		if (!temp)
		{
			ft_lstclear(&lst, del);
			ft_lstclear(&res, del);
			break ;
		}
		lst = lst->next;
		ft_lstadd_back(&res, temp);
	}
	return (res);
}
