/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:02:35 by fvarrin           #+#    #+#             */
/*   Updated: 2022/06/06 14:41:40 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>

#include "libft.h"
#include "minishell.h"

/**
 * Set the command input
 *
 * @param {t_command *} command
 * @param {char *} file_name
 *
 * @return {t_command *} command
 */
t_command	*set_input(t_command *command, char *file_name)
{
	command->in = ft_strdup(file_name);
	return (command);
}

/**
 * Set the command output
 *
 * @param {t_command *} command
 * @param {char *} file_name
 * @param {_Bool} append_mode
 *
 * @return {t_command *} command
 */
t_command	*set_output(t_command *command, char *file_name, _Bool append_mode)
{
	command->out = ft_strdup(file_name);
	command->out_in_append_mode = append_mode;
	return (command);
}

t_command	*handle_operator(t_command *command, char **argument)
{
	if (ft_strcmp(*argument, ">") == 0)
		set_output(command, *(argument + 1), false);
	else if (ft_strcmp(*argument, ">>") == 0)
		set_output(command, *(argument + 1), true);
	else if (ft_strcmp(*argument, "<") == 0)
		set_input(command, *(argument + 1));
	return (command);
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
t_list_el 	*get_io_from_words(t_list_el *words, t_command *command)
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
		else if (word->type == INPUT_SIMPLE_OPERATOR)
			command->in = ft_strdup(((t_token *)current_el->next->content)->word);
		else if (word->type == OUTPUT_SIMPLE_OPERATOR)
			command->out = ft_strdup(((t_token *)current_el->next->content)->word);
		else if (word->type == OUTPUT_APPEND_OPERATOR)
		{
			command->out = ft_strdup(((t_token *)current_el->next->content)->word);
			command->out_in_append_mode = true;
		}
		if (last_el)
		{
			ft_lstremove_next(last_el, delete_word);
			ft_lstremove_next(last_el, delete_word);
			current_el = last_el->next;
		}
		else
		{
			ft_lstremove_first(&words, delete_word);
			ft_lstremove_first(&words, delete_word);
			current_el = words;
		}
	}
	return (words);
}
