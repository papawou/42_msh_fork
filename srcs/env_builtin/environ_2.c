/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 01:22:37 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/23 20:00:21 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "libft.h"

//GETTERS
/**
 * return t_environ_el* if key == t_environ_el.key
 */
t_environ_el	*get_environ_el(t_list_el *entry, char *key)
{
	t_environ_el	*tmp;

	if (key == NULL || entry == NULL)
		return (NULL);
	while (entry)
	{
		tmp = entry->content;
		if (tmp != NULL && !ft_strncmp(key, tmp->key, ft_strlen(key)))
			return (tmp);
		entry = entry->next;
	}
	return (NULL);
}

/**
 * dup t_environ_el->value if key == t_environ_el.key
 * return NULL if key not found //?ft_strdup("")
 */
char	*getdup_environ_el_value(t_list_el *entry, char *key)
{
	t_environ_el	*tmp;

	if (entry == NULL || key == NULL)
		return (NULL);
	tmp = get_environ_el(entry, key);
	if (tmp == NULL)
		return (NULL);
	return (ft_strdup(tmp->value));
}
