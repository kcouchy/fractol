/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftlib_lstadd_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:16:43 by kcouchma          #+#    #+#             */
/*   Updated: 2023/12/04 16:01:57 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ftlib_lstadd_back(t_lblst **lst, t_lblst *new)
{
	while (*lst != NULL)
		lst = &(*lst)->next;
	*lst = new;
}
