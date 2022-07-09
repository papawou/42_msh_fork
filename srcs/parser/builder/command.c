/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:20:15 by fvarrin           #+#    #+#             */
/*   Updated: 2022/07/09 15:59:41 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

#include "libft.h"
#include "minishell.h"

t_execution_plan	*init_execution_plan_command(
		t_execution_plan *execution_plan,
		int number_of_commands
)
{
	execution_plan->commands = (t_command **)malloc(
			sizeof(t_command *) * number_of_commands);
	if (execution_plan->commands == NULL)
	{
		free(execution_plan);
		exit(ERR_ALLOCATING_MEMORY);
	}
	execution_plan->number_of_commands = number_of_commands;
	return (execution_plan);
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
	free(command->argv);
	free(command->bin);
	free(command->in);
	free(command->out);
	free(command);
}
