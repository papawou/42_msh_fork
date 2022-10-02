/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 13:06:01 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/01 13:17:55 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>

/**
 *
 * A wrapper around perror to add the shell name in the prefix
 *
 * @param {char *} error
 */
void	print_erno_error(char *error)
{
	char	*prefix;

	if (error != NULL)
		prefix = ft_strjoin(SHELL_NAME, error);
	else
		prefix = ft_strdup(SHELL_NAME);
	perror(prefix);
	free(prefix);
}
