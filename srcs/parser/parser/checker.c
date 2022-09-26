/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 14:21:02 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/25 15:57:51 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>

#include "minishell.h"

/**
 *
 * Display error message and return false for the calling function
 *
 * @param {char *} value
 *
 * @return {_Bool} always false
 */
_Bool	unexpected_token(char *value)
{
	if (value == NULL)
		value = "End of line";
	printf("Unexpected token near \"%s\"\n", value);
	return (false);
}

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
 * Check rules for simple input operator
 *
 * @param {t_list_el *} next_el
 *
 * @return {_Bool} is_valid
 */
static _Bool	verify_input_operator(
		t_list_el *lst,
		t_list_el *next_el,
		t_list_el *previous_el
	)
{
	int			number_of_words_after;
	int			number_of_words_before;

	if (previous_el == NULL)
	{
		number_of_words_after = 2;
		number_of_words_before = 0;
	}
	else
	{
		number_of_words_after = 1;
		number_of_words_before = 1;
		previous_el = lst;
	}
	if (!check_for_words(previous_el, number_of_words_before))
		return (false);
	if (!check_for_words(next_el, number_of_words_after))
		return (false);
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
static _Bool	verify_output_operator(t_list_el *next_el)
{
	int			number_of_words_after;

	number_of_words_after = 1;
	if (!check_for_words(next_el, number_of_words_after))
		return (false);
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
	t_list_el	*previous_el;
	t_token		*token;

	previous_el = NULL;
	current_el = tokens;
	while (current_el)
	{
		token = (t_token *)current_el->content;
		if (token->type == I_SIMPLE_OP || token->type == I_HEREDOC_OP)
		{
			if (verify_input_operator(tokens, current_el->next, previous_el)
				== false)
				return (false);
		}
		if (token->type == O_SIMPLE_OP || token->type == O_APPEND_OP)
		{
			if (verify_output_operator(current_el->next) == false)
				return (false);
		}
		previous_el = current_el;
		current_el = current_el->next;
	}
	return (true);
}
