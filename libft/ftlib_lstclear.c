/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftlib_lstclear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:01:32 by kcouchma          #+#    #+#             */
/*   Updated: 2023/12/04 16:01:57 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ftlib_lstclear(t_lblst **lst, void (*del)(void *))
{
	t_lblst	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		ftlib_lstdelone(*lst, del);
		*lst = temp;
	}
}
