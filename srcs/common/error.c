/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 13:06:01 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/07 10:15:06 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/**
 *
 * @param {char *} prefix
 * @param {char *} attribute
 * @param {char *} message
 */
void	print_custom_error(char *prefix, char *attribute, char *message)
{
	if (prefix && attribute && message)
		ft_printf_fd(STDERR_FILENO, "%s: %s: `%s`: %s\n",
			SHELL_NAME, prefix, attribute, message);
	else if (prefix && message)
		ft_printf_fd(STDERR_FILENO, "%s: %s: %s\n",
			SHELL_NAME, prefix, message);
	else if (message)
		ft_printf_fd(STDERR_FILENO, "%s: %s\n",
			SHELL_NAME, message);
}
