/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:01:32 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/23 14:25:41 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * delete an item in the list and set next correctly
 */
void	ft_lstremove(t_list_el **lst, t_list_el *item, void (*del)(void *))
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

t_list_el *ft_lstfind_by_content(t_list_el *entry, void *content)
{
	if (entry == NULL || content == NULL)
		return (NULL);
	while (entry)
	{
		if (entry->content == content)
			return (entry);
		entry = entry->next;
	}
	return (NULL);
}

/**
 * free 2d array until src[i] == NULL 
 */
void	free_char_2d(char **src)
{
	int	i;
	
	if (src == NULL)
		return ;
	i = 0;
	while (src[i])
	{
		free(src[i]);
		++i;
	}
	free(src);
}
