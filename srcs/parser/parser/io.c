/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:02:35 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/26 21:00:38 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#include <fcntl.h>

static int	get_file_mode_from_token(t_token *token)
{
	if (token->type == I_SIMPLE_OP)
		return (O_RDONLY);
	if (token->type == O_SIMPLE_OP)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	if (token->type == O_APPEND_OP)
		return (O_WRONLY | O_CREAT | O_APPEND);
	return (-1);
}

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
	char	*value;

	value = ((t_token *)current_el->next->content)->value;
	if (token->type == I_SIMPLE_OP)
	{
		command->in = init_file_redirect(value);
		command->in->mode = get_file_mode_from_token(token);
	}
	else if (token->type == O_SIMPLE_OP || token->type == O_APPEND_OP)
	{
		command->out = init_file_redirect(value);
		command->out->mode = get_file_mode_from_token(token);
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
		if (token->type == WORD_WO_ENV_EXP
			|| token->type == WORD_W_ENV_EXP
			|| token->type == SPACE_DELIMITER)
		{
			current_el = current_el->next;
			continue ;
		}
		handle_io_token(token, command, current_el);
		current_el = current_el->next;
	}
}
