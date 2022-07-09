/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:02:35 by fvarrin           #+#    #+#             */
/*   Updated: 2022/07/09 19:18:11 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>

#include "libft.h"
#include "minishell.h"

/**
 *
 * Set the in and out for the command according to the token type
 *
 * @param {t_toke *} token
 * @param {t_command *} command
 * @param [t_list_el *} current_el
 */
void	handle_io_token(
			t_token *token,
			t_command *command,
			t_list_el *current_el
			)
{
	if (token->type == INPUT_SIMPLE_OPERATOR)
		command->in = ft_strdup(((t_token *)current_el->next->content)->value);
	else if (token->type == OUTPUT_SIMPLE_OPERATOR)
		command->out = ft_strdup(((t_token *)current_el->next->content)->value);
	else if (token->type == OUTPUT_APPEND_OPERATOR)
	{
		command->out = ft_strdup(((t_token *)current_el->next->content)->value);
		command->out_in_append_mode = true;
	}
}

/**
 * If there is an infile or and outfile in the command
 * set the in and / or out properties and update tokens accordingly
 *
 * @param {char **} arguments
 * @param {t_command *} command
 *
 * @return {char **} arguments
 */
void	set_io_from_tokens(t_command *command)
{
	t_list_el	*current_el;
	t_token		*token;

	current_el = command->tokens;
	while (current_el)
	{
		token = (t_token *)current_el->content;
		if (token->type == WORD_WITHOUT_ENV_EXPANSION
			|| token->type == WORD_WITH_ENV_EXPANSION
			|| token->type == SPACE_DELIMITER)
		{
			current_el = current_el->next;
			continue ;
		}
		handle_io_token(token, command, current_el);
		current_el = current_el->next;
	}
}
