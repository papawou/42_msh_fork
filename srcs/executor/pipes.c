/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:29:02 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/25 15:46:20 by kmendes          ###   ########.fr       */
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
	pipes = (int **)malloc(sizeof(int *) * (total_number_of_processes));
	if (pipes == NULL)
		return (NULL);
	i = 0;
	while (i < total_number_of_processes)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (pipes[i] == NULL)
		{
			while (i--)
				free(pipes[i]);
			free(pipes);
			return (NULL);
		}
		++i;
	}
	return (pipes);
}

/**
 *
 * Allocate memory and creates the pipes.
 *
 * @param {int} number_of_child_processes
 * @param {int **} pipes
 *
 * @return {int **} pipes
 */
int	**create_pipes(int number_of_child_processes)
{
	int		**pipes;
	int		i;
	int		total_number_of_processes;

	pipes = allocate_pipes(number_of_child_processes);
	total_number_of_processes = count_total_process(number_of_child_processes);
	if (pipes == NULL)
		return (NULL);
	i = 0;
	while (i < total_number_of_processes)
	{
		if (pipe(pipes[i]) == -1)
		{
			while (i--)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
				destroy_pipes(number_of_child_processes, pipes);
				return (NULL);
			}
		}
		i++;
	}
	return (pipes);
}

/**
 *
 * Close all unnecessary pipes for a child process
 *
 * @param {int **} pipes
 * @param {int} number_of_child_processes
 * @param {int} index
 */
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

/**
 *
 * Close all unnecessary pipes for the main process
 *
 * @param {int} pipes
 * @param {int} number_of_child_processes
 */
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

/**
 * Free all the allocated memory to store pipes fd
 *
 * @param {int} number_of_child_processes
 * @param {int **} pipes
 */
void	destroy_pipes(int number_of_child_processes, int **pipes)
{
	int		total_number_of_processes;

	if (pipes == NULL)
		return ;
	total_number_of_processes = count_total_process(number_of_child_processes);
	while (total_number_of_processes--)
		free(pipes[total_number_of_processes]);
	free(pipes);
}
