/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:55:46 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/28 18:39:25 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <unistd.h>
#include <stdlib.h>

/**
 * Utility to get the total number of process from the number of child process.
 * The goal is to avoid the "1" magic number at several places
 *
 * @param {int} number_of_child_processes
 *
 * @return {int} total_number_of_processes
 */
int	count_total_process(int number_of_child_processes)
{
	return (number_of_child_processes + 1);
}

/**
 * Allocate memory for the pids and fork for every processes
 *
 * @param {t_execution_plan *} execution_plan
 * @param {int *} pids
 * @param {int **} pipes
 *
 * @return {int *} return a pointer to the pids
 */
int	*create_processes(t_execution_plan *execution_plan, int *pids, int **pipes)
{
	int		i;
	int		number_of_child_processes;

	number_of_child_processes = execution_plan->number_of_commands;
	pids = malloc(sizeof(int) * number_of_child_processes);
	i = 0;
	while (i < number_of_child_processes)
	{
		if (execution_plan->commands[i]->heredoc != NULL)
			execute_heredoc(execution_plan->commands[i]);
		if (execution_plan->need_to_fork)
			pids[i] = fork();
		else
			pids[i] = 0;
		if (pids[i] == -1)
			exit(ERR_FORKING_PROCESS);
		if (pids[i] == 0)
		{
			set_child_signals();
			close_pipes_in_child_process(pipes, number_of_child_processes, i);
			execute_command(execution_plan, pipes, i);
		}
		i++;
	}
	return (pids);
}
