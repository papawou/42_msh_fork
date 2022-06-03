/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:20:15 by fvarrin           #+#    #+#             */
/*   Updated: 2022/06/02 14:24:59 by fvarrin          ###   ########.fr       */
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
t_command	*init_command_argv(t_command *command)
{
	int			i;
	int			number_or_arguments;
	t_list_el	*last_el;
	t_list_el	*current_el;

	number_or_arguments = ft_lstsize(command->words);
	command->argv = (char **)malloc(sizeof(char *) * (number_or_arguments + 1));
	if (command->argv == NULL)
		exit(ERR_ALLOCATING_MEMORY);
	i = 0;
	current_el = command->words;
	while (current_el)
	{
		command->argv[i] = ft_strdup(((t_word *)current_el->content)->content);
		last_el = current_el;
		current_el = current_el->next;
		ft_lstdelone(last_el, delete_word);
		i++;
	}
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
	int		i;

	i = 0;
//	while (command->argv[i])
//		free(command->argv[i++]);
//	free(command->bin);
	free(command->in);
	free(command->out);
	free(command);
}
