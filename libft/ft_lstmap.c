/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:27:38 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:27:38 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include <stdlib.h>

static t_list	*create_mapped_node(void *content,
					void *(*f)(void *),
					void (*del)(void *),
					t_list **new_list)
{
	void	*new_content;
	t_list	*node;

	new_content = f(content);
	if (!new_content)
	{
		ft_lstclear(new_list, del);
		return (NULL);
	}
	node = ft_lstnew(new_content);
	if (!node)
	{
		del(new_content);
		ft_lstclear(new_list, del);
		return (NULL);
	}
	return (node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;

	if (!lst || !f)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_node = create_mapped_node(lst->content, f, del, &new_list);
		if (!new_node)
			return (NULL);
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
