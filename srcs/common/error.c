/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 13:06:01 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/02 14:14:24 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/**
 *
 * A wrapper around perror to add the shell name in the prefix
 *
 * @param {char *} error
 */
void	print_erno_error(char *error, int arg_errno)
{
	char	*prefix;

	if (error != NULL)
		prefix = ft_strjoin(SHELL_NAME, error);
	else
		prefix = ft_strdup(SHELL_NAME);
	errno = arg_errno;
	perror(prefix);
	free(prefix);
}


void	print_custom_error(char *prefix, char *message)
{
	if (prefix)
		ft_printf_fd(STDERR_FILENO, "%s: %s: %s\n", SHELL_NAME, prefix, message);
	else if (message)
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", SHELL_NAME, message);
}