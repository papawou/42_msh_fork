/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:02:35 by fvarrin           #+#    #+#             */
/*   Updated: 2022/06/06 15:07:49 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>

#include "libft.h"
#include "minishell.h"

/**
 *
 * When an io token is found, it wil be removed from the list and the current_el
 * is set accordingly
 *
 * @param {t_list_el **} last_el
 * @param {t_list_el **} current_el
 * @param {t_list_el **} words
 */
void	remove_io_words_from_list(
			t_list_el **last_el,
			t_list_el **current_el,
			t_list_el **words
			)
{
	if (*last_el)
	{
		ft_lstremove_next(*last_el, delete_word_token);
		ft_lstremove_next(*last_el, delete_word_token);
		*current_el = (*last_el)->next;
	}
	else
	{
		ft_lstremove_first(words, delete_word_token);
		ft_lstremove_first(words, delete_word_token);
		*current_el = *words;
	}
}

/**
 *
 * Set the in and out for the command according to the token type
 *
 * @param {t_toke *} word
 * @param {t_command *} command
 * @param [t_list_el *} current_el
 */
void	handle_io_token(
			t_token *word,
			t_command *command,
			t_list_el *current_el
			)
{
	if (word->type == INPUT_SIMPLE_OPERATOR)
		command->in = ft_strdup(((t_token *)current_el->next->content)->word);
	else if (word->type == OUTPUT_SIMPLE_OPERATOR)
		command->out = ft_strdup(((t_token *)current_el->next->content)->word);
	else if (word->type == OUTPUT_APPEND_OPERATOR)
	{
		command->out = ft_strdup(((t_token *)current_el->next->content)->word);
		command->out_in_append_mode = true;
	}
}

/**
 * If there is an infile or and outfile in the command
 * set the in and / or out properties and update words accordingly
 *
 * @param {char **} arguments
 * @param {t_command *} command
 *
 * @return {char **} arguments
 */
t_list_el	*get_io_from_words(t_list_el *words, t_command *command)
{
	t_list_el	*current_el;
	t_list_el	*last_el;
	t_token		*word;

	last_el = NULL;
	current_el = words;
	while (current_el)
	{
		word = (t_token *)current_el->content;
		if (word->type == WORLD_WITHOUT_ENV_EXPENSION
			|| word->type == WORLD_WITH_ENV_EXPENSION)
		{
			last_el = current_el;
			current_el = current_el->next;
			continue ;
		}
		handle_io_token(word, command, current_el);
		remove_io_words_from_list(&last_el, &current_el, &words);
	}
	return (words);
}
