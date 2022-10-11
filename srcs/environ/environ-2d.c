/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ-2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:11:03 by kmendes           #+#    #+#             */
/*   Updated: 2022/10/11 14:52:28 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdlib.h>
#include <stdio.h>

#define DECLARE "declare -x "

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
		if (((t_environ_el *)lst->content)->value != NULL)
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

void	handle_environ_el(t_list_el *lst, char **dst)
{
	char	*key;
	char	*value;
	char	*tmp;

	key = ft_strdup(((t_environ_el *)lst->content)->key);
	if (((t_environ_el *)lst->content)->value != NULL)
	{
		value = ft_strjoin("=\"", ((t_environ_el *)lst->content)->value);
		tmp = ft_strjoin(value, "\"");
		free(value);
		value = tmp;
	}
	else
		value = ft_strdup("");
	tmp = ft_strjoin_and_free(key, value);
	*dst = ft_strjoin(DECLARE, tmp);
	free(tmp);
}

char	**environ_el_to_char_2d_export(t_list_el *lst)
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
		handle_environ_el(lst, &dst[i]);
		i++;
		lst = lst->next;
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

void	print_environ_char_2d(char **char_2d)
{
	int		i;

	i = 0;
	while (char_2d[i])
		printf("%s\n", char_2d[i++]);
}
