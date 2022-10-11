/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 16:07:26 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/04 15:19:45 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>

/**
 *
 * Check if has more token in string
 *
 * @param {char *} str
 *
 * @return {_Bool} has_more_tokens
 */
_Bool	has_more_tokens(char *str)
{
	if (*str == '\0')
		return (false);
	return (true);
}

_Bool	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (true);
	return (false);
}
