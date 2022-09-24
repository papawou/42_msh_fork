/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:39:50 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/24 15:38:27 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "libft.h"

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

/**
 *
 * @param {t_list_el} **entry
 * @param {char *} key_value
 */
void	add_environ_el(t_list_el **entry, char *key_value)
{
	t_environ_el	*el;

	if (entry == NULL || key_value == NULL)
		return ;
	el = init_environ_el(key_value);
	if (el == NULL)
		return ;
	ft_lstadd_front(entry, ft_lstnew(el));
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
 * parse env variable from "key=value..." to struct s_environ_el
 *
 * @param {char *} key_value
 *
 * @return {t_environ_el *}
 */
t_environ_el	*init_environ_el(char *key_value)
{
	t_environ_el	*dst;	
	char			*idx;

	if (key_value == NULL)
		return (NULL);
	if (key_value[0] == 0)
		return (NULL);
	dst = (t_environ_el *) malloc(sizeof(t_environ_el));
	idx = ft_strchr(key_value, '=');
	if (idx == NULL || dst == NULL)
	{
		free(dst);
		return (NULL);
	}
	dst->key = ft_strndup(key_value, idx - key_value);
	dst->value = ft_strdup(idx + 1);
	if (dst->key != NULL && dst->value != NULL)
		return (dst);
	free(dst->key);
	free(dst->value);
	free(dst);
	return (NULL);
}

/**
 *
 * return t_environ_el* if key == t_environ_el.key
 *
 * @param {t_list_el *} entry
 * @param {char *} key
 *
 * @return {t_environ_el *}
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
