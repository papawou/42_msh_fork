/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator-utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 18:24:11 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/17 14:29:35 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>

/**
 * @param {char *} str
 *
 * @return  {_Bool} is_a_simple_output
 */
_Bool	is_a_simple_output(char *str)
{
	if (str[0] == '>')
		return (true);
	return (false);
}

/**
 * @param {char *} str
 *
 * @return  {_Bool} is_a_append_output
 */
_Bool	is_a_append_output(char *str)
{
	if (str[0] == '>' && str[1] == '>')
		return (true);
	return (false);
}

/**
 * @param {char *} str
 *
 * @return  {_Bool} is_a_simple_input
 */
_Bool	is_a_simple_input(char *str)
{
	if (str[0] == '<')
		return (true);
	return (false);
}

/**
 * @param {char *} str
 *
 * @return  {_Bool} is_a_heredoc_input
 */
_Bool	is_a_heredoc_input(char *str)
{
	if (str[0] == '<' && str[1] == '<')
		return (true);
	return (false);
}
