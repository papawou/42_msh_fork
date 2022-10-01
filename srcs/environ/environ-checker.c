/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ-checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 16:15:57 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/01 16:35:05 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>

/**
 *
 * Check if key_value param is a valid environment variable
 * formatted as #*[a-b,A-Z,0-9]=*.#
 * return addr of '=' if valid
 * return NULL if invalid
 *
 * @param {char *} key_value
 * @param {_Bool} accept_key_only
 *
 * @return {_Bool}
 */
_Bool	is_valid_key_value_env(char *key_value, _Bool accept_key_only)
{
	char	*eq_ptr;

	if (key_value == NULL)
		return (false);
	eq_ptr = ft_strchr(key_value, '=');
	if (!accept_key_only && (eq_ptr == NULL || eq_ptr == key_value))
		return (false);
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
