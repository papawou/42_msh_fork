/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:20:48 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/11 15:48:32 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>

#include "minishell.h"

#include <stdlib.h>

/**
 * Move current and last element from n position
 * Careful, when using this command, we need to be sure that there is n more
 * Elements as this function doesn't test it
 *
 * @param {t_list_el **} current_el_ptr
 * @param {t_list_el **} last_el_ptr
 * @param {int} n
 */
void	skip_n_elements(
		t_list_el **current_el_ptr,
		int n,
		_Bool count_spaces
		)
{
	int			i;
	t_list_el	*current_el;

	current_el = *current_el_ptr;
	i = 0;
	while (i < n)
	{
		if (count_spaces
			|| ((t_token *)current_el->content)->type != SPACE_DELIMITER)
			i++;
		current_el = current_el->next;
	}
	*current_el_ptr = current_el;
}

/**
 * Set argv[i] to the string and initialize a new empty string
 *
 * @param {t_command *} command
 * @param {char **} str
 * @param {int *} i
 */
void	set_next_argv_str(t_command *command, char **str, int *i)
{
	if (*str != NULL)
	{
		command->argv[(*i)++] = *str;
		*str = NULL;
	}
}

void	join_token_value(char **str, t_token *token)
{
	char	*tmp;

	if (*str == NULL)
		*str = create_empty_str();
	tmp = ft_strjoin(*str, token->value);
	free(*str);
	*str = tmp;
}

/**
 *
 * Define argv from the tokens
 *
 * @param {t_command *} command
 * @param {char **} str
 */
void	set_argv_from_tokens(t_command *command, char **str)
{
	int			i;
	t_list_el	*current_el;
	t_token		*token;

	i = 0;
	current_el = command->tokens;
	while (current_el)
	{
		token = (t_token *)current_el->content;
		if (is_io_token(token))
			skip_n_elements(&current_el, 2, false);
		if (token->type == WORD_W_ENV_EXP || token->type == WORD_WO_ENV_EXP)
			join_token_value(str, token);
		else if (token->type == SPACE_DELIMITER)
			set_next_argv_str(command, str, &i);
		skip_n_elements(&current_el, 1, true);
	}
	if (*str != NULL)
		command->argv[i++] = *str;
	command->argv[i] = NULL;
}
