/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:16:13 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/11 14:19:03 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

#include "minishell.h"

int	add_environ_el(t_list_el **entry, char *key_value)
{
	t_environ_el	*tmp;
	t_environ_el	parsed_el;

	if (key_value == NULL)
		return (1);
	if (parse_key_value_environ_el(key_value, &parsed_el))
		return (1);
	tmp = get_environ_el(*entry, parsed_el.key);
	if (tmp)
	{
		free(tmp->value);
		tmp->value = parsed_el.value;
		return (0);
	}
	tmp = create_environ_el(parsed_el.key, parsed_el.value);
	if (tmp == NULL)
		return (1);
	ft_lstadd_front(entry, ft_lstnew(tmp));
	return (0);
}

t_environ_el	*create_environ_el(char *key, char *value)
{
	t_environ_el	*dst;

	if (key == NULL)
		return (NULL);
	dst = (t_environ_el *) malloc(sizeof(t_environ_el));
	dst->key = key;
	dst->value = value;
	return (dst);
}

t_environ_el	*get_environ_el(t_list_el *entry, char *key)
{
	t_environ_el	*tmp;

	if (entry == NULL || key == NULL)
		return (NULL);
	while (entry)
	{
		tmp = (t_environ_el *) entry->content;
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		entry = entry->next;
	}
	return (NULL);
}

/**
 *
 * @param {t_list_el **} entry
 * @param {char *} key
 */
void	remove_environ_el(t_list_el **entry, char *key)
{
	t_environ_el	*el;

	if (entry == NULL || key == NULL)
		return ;
	el = get_environ_el(*entry, key);
	ft_lstremove(entry, ft_lstfind_by_content(*entry, el), &destroy_environ_el);
}

/**
 *
 * use it for ft_lstdel(..., void (*del)(void *))
 *
 * @param {void *} el
 */
void	destroy_environ_el(void *el)
{
	if (el == NULL)
		return ;
	free(((t_environ_el *)el)->key);
	free(((t_environ_el *)el)->value);
	free(el);
}
