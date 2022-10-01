/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 16:44:35 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/01 14:10:11 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>

/**
 *
 * Check if one of the tokens is a heredoc input
 *
 * @param tokens
 * @return
 */
_Bool	has_heredoc_token(t_list_el *tokens)
{
	t_list_el	*current_el;
	t_token		*token;

	current_el = tokens;
	while (current_el)
	{
		token = (t_token *)current_el->content;
		if (token->type == PIPE)
			return (false);
		if (token->type == I_HEREDOC_OP)
			return (true);
		current_el = current_el->next;
	}
	return (false);
}
