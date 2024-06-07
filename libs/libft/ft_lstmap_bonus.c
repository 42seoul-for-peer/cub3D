/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:15:04 by hyeunkim          #+#    #+#             */
/*   Updated: 2023/11/18 14:09:55 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*start;

	if (!lst)
		return (NULL);
	start = ft_lstnew(0);
	if (!start)
		return (NULL);
	start->content = f(lst->content);
	lst = lst->next;
	result = start;
	while (lst)
	{
		result->next = ft_lstnew(0);
		if (!result->next)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		result->next->content = f(lst->content);
		lst = lst->next;
		result = result->next;
	}
	return (start);
}
