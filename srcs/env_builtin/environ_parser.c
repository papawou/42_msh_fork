/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:11:03 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/24 15:06:52 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "libft.h"

/**
 *
 * parse char **environ from unistd.h to a linked list
 * and return it
 * return value is NULL if environ vars is empty /== environ[0] == NULL
 *
 * @return {t_list_el *}
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
