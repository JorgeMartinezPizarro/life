/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:27:25 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:27:25 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstclone(t_list *lst, void *(*dup)(void *))
{
	t_list	*copy;
	t_list	*node;

	copy = NULL;
	while (lst)
	{
		node = ft_lstnew(dup(lst->content));
		if (!node)
		{
			ft_lstclear(&copy, free);
			return (NULL);
		}
		ft_lstadd_back(&copy, node);
		lst = lst->next;
	}
	return (copy);
}
