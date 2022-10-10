/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution-plan.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 15:45:35 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/10 18:40:56 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

#include "minishell.h"

/**
 * Allocate memory for the execution plan and fill up number_of_command property
 *
 * @param {int} number_of_commands
 *
 * @return {t_execution_plan *}
 */
t_execution_plan	*init_execution_plan(int number_of_commands)
{
	t_execution_plan	*execution_plan;

	execution_plan = malloc(sizeof(t_execution_plan));
	if (execution_plan == NULL)
		exit(ERR_ALLOCATING_MEMORY);
	execution_plan->commands = ft_calloc(number_of_commands, sizeof(t_command));
	if (execution_plan->commands == NULL)
	{
		free(execution_plan);
		exit(ERR_ALLOCATING_MEMORY);
	}
	execution_plan->number_of_commands = number_of_commands;
	execution_plan->need_to_fork = true;
	return (execution_plan);
}

/**
 * Free all execution plan memory
 *
 * @param {t_execution_plan *} execution_plan
 */
void	destroy_execution_plan(t_execution_plan *execution_plan)
{
	int		i;

	i = 0;
	while (i < execution_plan->number_of_commands)
		destroy_command(execution_plan->commands[i++]);
	free(execution_plan->commands);
	free(execution_plan);
}
