/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution-plan.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 15:45:35 by fvarrin           #+#    #+#             */
/*   Updated: 2022/07/09 17:47:08 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

/**
 * Allocate memory for the execution plan and fill up number_of_command property
 *
 * @param {int} number_of_commands
 *
 * @return {t_execution_plan *}
 */
t_execution_plan	*init_execution_plan(void)
{
	t_execution_plan	*execution_plan;

	execution_plan = malloc(sizeof(t_execution_plan));
	if (execution_plan == NULL)
		exit(ERR_ALLOCATING_MEMORY);
	return (execution_plan);
}

/**
 * Free all execution plan memory
 *
 * @param {t_execution_plan *} execution_plan
 */
void	destroy_execution_plan(t_execution_plan *execution_plan)
{
	free(execution_plan->commands);
	free(execution_plan);
}
