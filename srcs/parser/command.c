/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:20:15 by fvarrin           #+#    #+#             */
/*   Updated: 2022/06/06 15:03:02 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

#include "libft.h"
#include "minishell.h"

/**
 * Allocate memory and copy the words in the command->argv array
 *
 * @param {t_command *} command
 * @param {char **} arguments
 *
 * @return {t_command *} command
 */
t_command	*set_command_argv(t_command *command)
{
	int			i;
	int			number_or_arguments;
	t_list_el	*current_el;

	number_or_arguments = ft_lstsize(command->words);
	command->argv = (char **)malloc(sizeof(char *) * (number_or_arguments + 1));
	if (command->argv == NULL)
		exit(ERR_ALLOCATING_MEMORY);
	i = 0;
	current_el = command->words;
	while (current_el)
	{
		command->argv[i] = ((t_token *)current_el->content)->word;
		current_el = current_el->next;
		i++;
	}
	command->argv[i] = NULL;
	return (command);
}

/**
 * Allocate memory for a command
 *
 * @return {t_command *} command
 */
t_command	*init_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (command == NULL)
		exit(ERR_ALLOCATING_MEMORY);
	command->in = NULL;
	command->out = NULL;
	command->argv = NULL;
	command->out_in_append_mode = false;
	return (command);
}

/**
 * Free all command memory
 *
 * @param {t_command *} command
 * @return {t_command *}
 */
void	destroy_command(t_command *command)
{
	ft_lstclear(&command->words, delete_word_token);
	free(command->argv);
	free(command->bin);
	free(command->in);
	free(command->out);
	free(command);
}
