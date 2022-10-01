/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 16:44:35 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/26 20:38:46 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
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

/**
 *
 * Set heredoc in command, set input as tmp file and remove heredoc
 * tokens from list
 *
 * @param {t_command *} command
 */
void	handle_heredoc_input(t_command *command)
{
	t_list_el	*current_el;
	t_token		*token;

	current_el = command->tokens;
	while (current_el)
	{
		token = (t_token *)current_el->content;
		if (token->type == I_HEREDOC_OP)
		{
			command->heredoc
				= ft_strdup(((t_token *)current_el->next->content)->value);
			command->in = init_file_redirect(TMP_FILE);
			ft_lstremove(&command->tokens, current_el->next, &destroy_token);
			ft_lstremove(&command->tokens, current_el, &destroy_token);
			break ;
		}
		current_el = current_el->next;
	}
}
