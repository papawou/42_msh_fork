/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:14:09 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/04 14:26:25 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>

#include "libft.h"
#include "minishell.h"

/**
 * Return a new string trimmed of spaces.
 * It free source and allocate memory for the new string
 *
 * @param {char *} source
 * @return {char *} dst
 */
char	*trim_space(char *source)
{
	char	*dst;

	dst = ft_strtrim(source, "\t\n\v\f\r ");
	free(source);
	return (dst);
}

/**
 *
 * Open a file and return the file descriptor
 *
 * @param {char *} path
 * @param {int} flags
 *
 * @return {int} fd
 */
int	open_file(char *path, int flags)
{
	int		fd;

	fd = open(path, flags, FILE_PERMISSION_IF_CREATED);
	if (fd < 0)
		exit(ERR_OPENING_FILE);
	return (fd);
}

/**
 *
 * Create a str of one null character on the heap that can be free
 *
 * @return  {char *} str
 */
char	*create_base_str(void)
{
	char	*str;

	str = malloc(sizeof(char));
	str[0] = '\0';
	return (str);
}
