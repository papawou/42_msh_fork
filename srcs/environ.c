/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 01:22:37 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/23 11:53:23 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/**
 * parse env variable from "key=value..." to struct s_environ_el
 */

t_environ_el	*create_environ_el(char *key_value)
{
	t_environ_el	*dst;	
	int				idx;

	if (key_value == NULL)
		return (NULL);
	if (key_value[0] == 0)
		return (NULL);
	dst = (t_environ_el *) malloc(sizeof(t_environ_el));
	if (dst == NULL)
		return (NULL);
	idx = ft_strchr(key_value, '=');
	dst->key = ft_strndup(key_value, idx);
	dst->key_len = ft_strlen(dst->key);
	dst->value = ft_strdup(&key_value[idx + 1]);
	dst->value_len = ft_strlen(dst->value);
	return (dst);
}

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
		ft_lstadd_front(&lst, ft_lstnew(create_environ_el(environ[i])));
		++i;
	}
	return (lst);
}

/**
 * return t_environ_el* if key == t_environ_el.key
 */
t_environ_el	*get_environ_el(char *key, t_list_el *entry)
{
	t_environ_el	*tmp;

	while (entry)
	{
		tmp = entry->content;
		if (ft_strncmp(key, tmp->key, ft_strlen(key)))
			return (tmp);
		entry = entry->next;
	}
	return (NULL);
}

/**
 * dup t_environ_el->value if key == t_environ_el.key
 * return NULL if key not found //?ft_strdup("")
 */
char	*getdup_environ_el_value(char *key, t_list_el *entry)
{
	t_environ_el	*tmp;

	tmp = get_environ_el(key, entry);
	if (tmp == NULL)
		return (NULL);
	return (ft_strdup(tmp->value));
}

char	**t_list_environ_el_to_char_2d(t_list_el *entry)
{
	char		**dst;
	int			size;
	t_list_el	el;
	char		*buf;
	
	size = ft_lstsize(entry);
	dst = malloc(sizeof(char *) * (size + 1));
	if (dst == NULL)
		return (NULL);
	dst[size] = NULL;

	int i = 0;
	while (entry)
	{
		dst[i] = NULL;
		dst[i] = ft_strjoin_and_free(ft_strjoin(((t_environ_el *)entry->content)->key, "="), ft_strdup(((t_environ_el *)entry->content)->value));
		entry = entry->next;
		if (dst[i] == NULL)
			continue ;	
		++i ;
	}
	return (dst);
}

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
