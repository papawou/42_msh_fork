/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 01:22:37 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/23 17:36:25 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "libft.h"

/**
 * use it for ft_lstdel(..., void (*del)(void *)) 
 */
void	del_environ_el(void *el)
{
	if (el == NULL)
		return ;
	free(((t_environ_el *)el)->key);
	free(((t_environ_el *)el)->value);
	free(el);
}

void	add_environ_el(t_list_el **entry, char *key_value)
{
	t_environ_el	*el;

	if (entry == NULL || key_value == NULL)
		return ;
	el = create_environ_el(key_value);
	if (el == NULL)
		return ;
	ft_lstadd_front(entry, ft_lstnew(el));
}

void	remove_environ_el(t_list_el **entry, char *key)
{
	t_environ_el	*el;

	if (entry == NULL || key == NULL)
		return ;
	el = get_environ_el(*entry, key);
	ft_lstremove(entry, ft_lstfind_by_content(*entry, el), &del_environ_el);
}

/**
 * parse env variable from "key=value..." to struct s_environ_el
 */
t_environ_el	*create_environ_el(char *key_value)
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
	dst->key_len = ft_strlen(dst->key);
	dst->value = ft_strdup(idx + 1);
	dst->value_len = ft_strlen(dst->value);
	if (dst->key != NULL && dst->value != NULL)
		return (dst);
	free(dst->key);
	free(dst->value);
	free(dst);
	return (NULL);
}

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

//TOSTRING PARER
/**
 * parse char **environ from unistd.h to a linked list
 * and return it
 * return value is NULL if environ vars is empty /== environ[0] == NULL
 */
t_list_el	*parse_environ(void)
{
	int				i;
	t_list_el		*lst;

	i = 0;
	lst = NULL;
	while (environ[i])
	{
		add_environ_el(&lst, environ[i]);
		++i;
	}
	return (lst);
}

/**
 * format list to 2d char
 */
char	**t_list_environ_el_to_char_2d(t_list_el *entry)
{
	char	**dst;
	int		i;

	if (entry == NULL)
		return (NULL);
	dst = malloc(sizeof(char *) * (ft_lstsize(entry) + 1));
	if (dst == NULL)
		return (NULL);
	ft_bzero(dst, sizeof(char *) * (ft_lstsize(entry) + 1));
	i = 0;
	while (entry)
	{
		dst[i] = ft_strjoin_and_free(
				ft_strjoin(((t_environ_el *)entry->content)->key, "="),
				ft_strdup(((t_environ_el *)entry->content)->value));
		entry = entry->next;
		if (dst[i] == NULL)
			continue ;
		++i ;
	}
	return (dst);
}
