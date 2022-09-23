/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 01:22:37 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/23 02:29:28 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

typedef struct s_environ_el {
	char *key;
	int	key_len;
	char *value;
	int value_len;
} t_environ_el;


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
	int						idx;

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

t_list_el *parse_environ(void)
{
	int						i;
	t_list_el			*lst;

	i = 0;
	lst = NULL;
	while (environ[i])
	{
		ft_lstadd_front(&lst, ft_lstnew(create_environ_el(environ[i])));
		++i;
	}
	return (lst);
}


t_environ_el	*get_environ_value(char *env)
{
	
}