/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftlib_lstmap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:06:53 by kcouchma          #+#    #+#             */
/*   Updated: 2023/12/04 16:01:57 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lblst	*ftlib_lstmap(t_lblst *lst, void *(*f)(void *), void (*del)(void *))
{
	t_lblst	*new_list;
	t_lblst	*new_node;
	t_lblst	*temp;

	new_list = NULL;
	temp = lst;
	while (temp)
	{
		new_node = ftlib_lstnew(NULL);
		if (!new_node)
		{
			ftlib_lstclear(&new_list, del);
			return (NULL);
		}
		new_node->content = f(temp->content);
		ftlib_lstadd_back(&new_list, new_node);
		temp = temp->next;
	}
	return (new_list);
}
