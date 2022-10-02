/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:38:35 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/25 15:57:52 by fvarrin          ###   ########.fr       */
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
	if (is_a_pipe(str))
		return (true);
	if (is_a_append_output(str))
		return (true);
	if (is_a_simple_output(str))
		return (true);
	if (is_a_heredoc_input(str))
		return (true);
	if (is_a_simple_input(str))
		return (true);
	return (false);
}

/**
 * Return true if is an operator symbol (`<`, `>` or `|`)
 * @param {char} c
 *
 * @return {_Bool}
 */
_Bool	is_operator_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

/**
 * Move the string until is neither an operator symbol nor a space
 * and re-assign the string pointer to the new position
 *
 * @param {char **} str
 */
void	eat_operator(char **str)
{
	while (is_operator_symbol(**str) || **str == ' ')
		*str = &((*str)[1]);
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
	else if (is_a_append_output(*str) == true)
		token->type = O_APPEND_OP;
	else if (is_a_simple_output(*str) == true)
		token->type = O_SIMPLE_OP;
	else if (is_a_heredoc_input(*str) == true)
		token->type = I_HEREDOC_OP;
	else if (is_a_simple_input(*str) == true)
		token->type = I_SIMPLE_OP;
	eat_operator(str);
}
