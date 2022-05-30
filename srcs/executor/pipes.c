/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:29:02 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/30 16:50:25 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/**
 *
 * Allocate memory for pipes to connect all processes.
 *
 * @param number_of_child_processes
 *
 * @return {int **} pointer on allocated pipes array
 */
static int	**allocate_pipes(int number_of_child_processes)
{
	int		**pipes;
	int		i;
	int		total_number_of_processes;

	total_number_of_processes = count_total_process(number_of_child_processes);
	i = 0;
	pipes = (int **)malloc(sizeof(int *) * (total_number_of_processes));
	while (i < total_number_of_processes)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
	return (pipes);
}

int	**create_pipes(int number_of_child_processes, int **pipes)
{
	int		i;
	int		total_number_of_processes;

	pipes = allocate_pipes(number_of_child_processes);
	total_number_of_processes = number_of_child_processes + 1;
	i = 0;
	while (i < total_number_of_processes)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("test");
			exit(-2);
		}
		i++;
	}
	return (pipes);
}

void	close_pipes_in_child_process(
		int **pipes,
		int number_of_child_processes,
		int index
	)
{
	int		i;
	int		total_number_of_processes;

	total_number_of_processes = count_total_process(number_of_child_processes);
	i = 0;
	while (i < total_number_of_processes)
	{
		if (index != i)
			close(pipes[i][0]);
		if (index + 1 != i)
			close(pipes[i][1]);
		i++;
	}
}

void	close_pipes_in_main_process(
		int **pipes,
		int number_of_child_processes
)
{
	int		i;
	int		total_number_of_processes;

	total_number_of_processes = count_total_process(number_of_child_processes);
	i = 0;
	while (i < total_number_of_processes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	destroy_pipes(int number_of_child_processes, int **pipes)
{
	int		i;
	int		total_number_of_processes;

	i = 0;
	total_number_of_processes = count_total_process(number_of_child_processes);
	while (i < total_number_of_processes)
	{
		if (pipes[i])
			free(pipes[i]);
		i++;
	}
	if (pipes)
		free(pipes);
}
