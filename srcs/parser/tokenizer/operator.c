/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:38:35 by fvarrin           #+#    #+#             */
/*   Updated: 2022/07/09 18:25:15 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>

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

void	set_operator(char **str, t_token *token)
{
	if (is_a_pipe(*str) == true)
		token->type = PIPE;
	else if (is_a_simple_output(*str) == true)
		token->type = OUTPUT_SIMPLE_OPERATOR;
	else if (is_a_append_output(*str) == true)
		token->type = OUTPUT_APPEND_OPERATOR;
	else if (is_a_simple_input(*str) == true)
		token->type = INPUT_SIMPLE_OPERATOR;
	else if (is_a_heredoc_input(*str) == true)
		token->type = INPUT_HEREDOC_OPERATOR;
	*str = &((*str)[3]);
}
