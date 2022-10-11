/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 13:06:01 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/11 08:28:04 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

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

/**
 *
 * Display error message and return false for the calling function
 *
 * @param {char *} value
 *
 * @return {_Bool} always false
 */
_Bool	unexpected_token(char *value)
{
	if (value == NULL)
		value = "End of line";
	printf(
		"%s: syntax error near unexpected token `%s`\n",
		SHELL_NAME, value);
	g_env_exit = 2;
	return (false);
}
