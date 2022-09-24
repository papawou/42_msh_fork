/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ-2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:11:03 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/24 17:18:23 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "libft.h"

/**
 *
 * format list to 2d char
 *
 * @param {t_list_el *} lst
 *
 * @return {char **}
 */
char	**environ_el_to_char_2d(t_list_el *lst)
{
	char	**dst;
	int		i;

	if (lst == NULL)
		return (NULL);
	dst = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (lst)
	{
		dst[i] = ft_strjoin_and_free(
				ft_strjoin(((t_environ_el *)lst->content)->key, "="),
				ft_strdup(((t_environ_el *)lst->content)->value));
		lst = lst->next;
		if (dst[i] == NULL)
			continue ;
		++i ;
	}
	return (dst);
}

/**
 *
 * free 2d array until src[i] == NULL
 *
 * @param {char **} src
 */
void	free_environ_char_2d(char **src)
{
	int	i;

	if (src == NULL)
		return ;
	i = 0;
	while (src[i])
		free(src[i++]);
	free(src);
}
