/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:02:35 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/10 18:40:56 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#include <fcntl.h>
#include <stdbool.h>

static int	get_file_mode_from_token(t_token *token)
{
	if (token->type == I_SIMPLE_OP || token->type == I_HEREDOC_OP)
		return (O_RDONLY);
	if (token->type == O_SIMPLE_OP)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	if (token->type == O_APPEND_OP)
		return (O_WRONLY | O_CREAT | O_APPEND);
	return (-1);
}

_Bool	is_io_token(t_token *token)
{
	if (token->type == O_SIMPLE_OP || token->type == O_APPEND_OP
		|| token->type == I_SIMPLE_OP || token->type == I_HEREDOC_OP)
		return (true);
	return (false);
}

char	*get_io_value(t_list_el *current_el)
{
	t_token		*token;

	while (current_el)
	{
		token = (t_token *)current_el->content;
		if (token->type != SPACE_DELIMITER)
			return (token->value);
		current_el = current_el->next;
	}
	return (NULL);
}

/**
 *
 * Set the in and out for the command according to the token type
 *
 * @param {t_toke *} token
 * @param {t_command *} command
 * @param [t_list_el *} current_el
 */
void	parse_io_token(
			t_token *token,
			t_command *command,
			t_list_el *current_el
			)
{
	char			*value;
	t_file_redirect	*file_redirect;

	if (is_io_token(token))
	{
		value = get_io_value(current_el->next);
		if (token->type == I_HEREDOC_OP)
		{
			ft_lstadd_back(&command->heredoc, ft_lstnew(ft_strdup(value)));
			file_redirect = init_file_redirect(TMP_FILE);
		}
		else
			file_redirect = init_file_redirect(value);
		file_redirect->mode = get_file_mode_from_token(token);
		if (token->type == I_SIMPLE_OP || token->type == I_HEREDOC_OP)
			ft_lstadd_back(&command->in, ft_lstnew(file_redirect));
		else
			ft_lstadd_back(&command->out, ft_lstnew(file_redirect));
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
		parse_io_token(token, command, current_el);
		current_el = current_el->next;
	}
}
