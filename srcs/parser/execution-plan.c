/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution-plan.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 15:45:35 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/29 16:47:47 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <stdlib.h>

#include "minishell.h"

t_execution_plan *init_execution_plan(int number_of_commands)
{
	t_execution_plan	*execution_plan;

	execution_plan = malloc(sizeof(t_execution_plan));
	if (execution_plan == NULL)
		exit(ERR_ALLOCATING_MEMORY);
	execution_plan->commands =
			(t_command **)malloc(sizeof(t_command *) * number_of_commands);
	if (execution_plan->commands == NULL)
	{
		free(execution_plan);
		exit(ERR_ALLOCATING_MEMORY);
	}
	execution_plan->number_of_commands = number_of_commands;
	return (execution_plan);
}

t_execution_plan	*destroy_execution_plan(t_execution_plan *execution_plan)
{
	int		i;

	i = 0;
	while (i < execution_plan->number_of_commands)
		destroy_command(execution_plan->commands[i++]);
	free(execution_plan->commands);
	free(execution_plan);
	return (NULL);
}