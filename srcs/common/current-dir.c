/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   current-dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:44:18 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/25 17:49:03 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

/**
 *
 * Return an allocated string holding the current working directory
 *
 * @return {char *}
 */
char	*get_current_dir(void)
{
	const int		buf_size = 1024;
	char			*current_dir;

	current_dir = malloc(sizeof(char) * buf_size);
	getcwd(current_dir, buf_size);
	return (current_dir);
}