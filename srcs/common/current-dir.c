/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   current-dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:44:18 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/01 13:06:45 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>

/**
 *
 * Return an allocated string holding the current working directory
 *
 * @return {char *}
 */
char	*get_current_dir(void)
{
	char		*current_dir;

	current_dir = malloc(sizeof(char) * PATH_MAX);
	if (current_dir == NULL)
		return (NULL);
	if (getcwd(current_dir, PATH_MAX) == NULL)
	{
		print_custom_error(NULL, NULL, strerror(errno));
		free(current_dir);
		return (NULL);
	}
	return (current_dir);
}
