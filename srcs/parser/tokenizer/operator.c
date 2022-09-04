/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:38:35 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/04 15:14:53 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>

/**
 * Define if a string is an operator
 *
 * @param {char *} str
 * `
 * @return {_Bool} is_an_operator
 */
_Bool	is_an_operator(char *str)
{
	if (str[0] != ' ')
		return (false);
	if (is_a_pipe(str))
		return (true);
	if (is_a_simple_output(str))
		return (true);
	if (is_a_simple_input(str))
		return (true);
	if (is_a_append_output(str))
		return (true);
	if (is_a_heredoc_input(str))
		return (true);
	return (false);
}

/**
 * Set the correct operator type to a given token
 *
 * @param {char **} str
 * @param {t_token *} token
 */
void	set_operator(char **str, t_token *token)
{
	if (is_a_pipe(*str) == true)
		token->type = PIPE;
	else if (is_a_simple_output(*str) == true)
		token->type = O_SIMPLE_OP;
	else if (is_a_append_output(*str) == true)
		token->type = O_APPEND_OP;
	else if (is_a_simple_input(*str) == true)
		token->type = I_SIMPLE_OP;
	else if (is_a_heredoc_input(*str) == true)
		token->type = I_HEREDOC_OP;
	*str = &((*str)[3]);
}
