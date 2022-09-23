/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:01:32 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/23 11:08:34 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_lstdel
 * delete an item in the list and set next correctly
 */
void ft_lstdel(t_list_el **lst, t_list_el *item, void (*del)(void *))
{
	t_list_el	*tmp;

	if (lst == NULL || item == NULL)
		return ;
	tmp = *lst;
	if (tmp == item)
	{
		*lst = item->next;
		ft_lstdelone(item, del);
		return ;
	}
	while (tmp)
	{
		if (tmp->next == item)
		{
			tmp->next = item->next;
			ft_lstdelone(item, del);
			return ;
		}
		tmp = tmp->next;
	}
}
