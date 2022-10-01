/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ-utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 16:15:57 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/01 19:39:58 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>
#include <stdlib.h>

/**
 *
 * Check if key_value param is a valid environment variable
 * formatted as #*[a-b,A-Z,0-9]=*.#
 *
 * @param {char *} key_value
 * @param {_Bool} accept_key_only
 *
 * @return {_Bool}
 */
_Bool	is_valid_key_value_env(char *key_value)
{
	char	*eq_ptr;

	if (key_value == NULL)
		return (false);
	eq_ptr = ft_strchr(key_value, '=');
	if (!ft_isalpha(key_value[0]))
		return (false);
	while (*key_value && key_value != eq_ptr)
	{
		if (!ft_isalnum(*key_value))
			return (false);
		++key_value;
	}
	return (true);
}

_Bool	extract_key_value(char *key_value, char **key, char **value)
{
	char	*eq_ptr;

	if (!key_value || (!key && !value))
		return (false);
	eq_ptr = ft_strchr(key_value, '=');
	if (eq_ptr == NULL)
		return (false);
	if (key)
	{
		*key = ft_strndup(key_value, eq_ptr - key_value);
		if (*key == NULL)
			return (false);
	}
	if (value)
	{
		*value = ft_strdup(eq_ptr + 1);
		if (*value == NULL)
		{
			free(*key);
			*key = NULL;
			return (false);
		}
	}
	return (true);
}
