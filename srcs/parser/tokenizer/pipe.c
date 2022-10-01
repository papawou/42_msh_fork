/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:02:51 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/01 15:06:52 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>

/**
 * @param {char *} str
 *
 * @return  {_Bool} is_a_pipe
 */
_Bool	is_a_pipe(char *str)
{
	if (str[0] == '|')
		return (true);
	return (false);
}

/**
 * Move the string until is neither a pipe symbol nor a space
 * and re-assign the string pointer to the new position
 *
 * @param {char **} str
 */
static void	eat_pipe(char **str)
{
	while (**str == '|' || **str == ' ')
		*str = &((*str)[1]);
}

/**
 * Set the type to pipe to a given token
 *
 * @param {char **} str
 * @param {t_token *} token
 */
void	set_pipe(char **str, t_token *token)
{
	token->type = PIPE;
	eat_pipe(str);
}
