/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:11:03 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/23 19:54:05 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "libft.h"

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
char	**list_environ_el_to_char_2d(t_list_el *entry)
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
