/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 14:21:02 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/10 18:40:56 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>

#include "minishell.h"

/**
 *
 * Check that there is number of words after el
 *
 * @param {t_list_el *} el
 * @param {int} number
 *
 * @return {_Bool}
 */
static _Bool	check_for_words(t_list_el *el, int number)
{
	t_token	*token;
	int		i;

	i = 0;
	while (i < number)
	{
		if (el == NULL)
			return (unexpected_token(NULL));
		token = (t_token *)el->content;
		if (token->type == SPACE_DELIMITER)
		{
			el = el->next;
			continue ;
		}
		if (token->type != WORD_W_ENV_EXP && token->type != WORD_WO_ENV_EXP)
			return (unexpected_token(token->value));
		el = el->next;
		i++;
	}
	return (true);
}

/**
 *
 * Check rules for output operator
 *
 * @param {t_list_el *} next_el
 *
 * @return {_Bool} is_valid
 */
static _Bool	verify_io_operator(t_list_el *next_el)
{
	int			number_of_words_after;

	number_of_words_after = 1;
	if (!check_for_words(next_el, number_of_words_after))
		return (false);
	return (true);
}

static _Bool	verify_has_non_space_tokens(t_list_el *tokens)
{
	t_list_el	*current_el;
	t_token		*token;

	current_el = tokens;
	while (current_el)
	{
		token = (t_token *)current_el->content;
		if (token->type != SPACE_DELIMITER)
			return (true);
		current_el = current_el->next;
	}
	unexpected_token(token->value);
	return (false);
}

_Bool	verify_first_is_not_pipe(t_list_el *tokens)
{
	t_list_el	*current_el;
	t_token		*token;

	current_el = tokens;
	while (current_el)
	{
		token = current_el->content;
		if (token->type == PIPE)
			return (unexpected_token(token->value));
		else if (token->type == SPACE_DELIMITER)
			current_el = current_el->next;
		else
			break ;
	}
	return (true);
}

/**
 * Verify that tokens are valid following some rules. For instance a output
 * operator need to be followed by a word
 *
 * @param {t_list_el *} tokens
 *
 * @return {_Bool} is_valid
 */
_Bool	verify_tokens(t_list_el *tokens)
{
	t_list_el	*current_el;
	t_token		*token;

	current_el = tokens;
	if (verify_has_non_space_tokens(tokens) == false)
		return (false);
	while (current_el)
	{
		token = (t_token *)current_el->content;
		if (token->type == O_SIMPLE_OP || token->type == O_APPEND_OP
			|| token->type == I_SIMPLE_OP || token->type == I_HEREDOC_OP)
		{
			if (verify_io_operator(current_el->next) == false)
				return (false);
		}
		current_el = current_el->next;
	}
	return (true);
}
