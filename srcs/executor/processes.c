/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:55:46 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/10 18:19:06 by kmendes          ###   ########.fr       */
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
 *
 * @param {t_execution_plan *} execution_plan
 * @param {int **} pipes
 * @param {int} index
 */
void	handle_child_process_execution(
			t_execution_plan *execution_plan,
			int **pipes,
			int index
		)
{
	int		number_of_child_processes;
	int		cmd_ret;

	number_of_child_processes = execution_plan->number_of_commands;
	set_child_signals();
	close_pipes_in_child_process(pipes, number_of_child_processes, index);
	cmd_ret = execute_command(execution_plan, pipes, index);
	destroy_pipes(number_of_child_processes, pipes);
	destroy_execution_plan(execution_plan);
	ft_lstclear(execution_plan->env, &destroy_environ_el);
	exit(cmd_ret);
}

/**
 * Fork for every processes and execute the command
 *
 * @param {t_execution_plan *} execution_plan
 * @param {int **} pipes
 *
 * @return {int} return the last pid
 */
int	create_processes(t_execution_plan *execution_plan, int **pipes)
{
	int		i;
	int		number_of_child_processes;
	int		last_pid;

	number_of_child_processes = execution_plan->number_of_commands;
	i = 0;
	while (i < number_of_child_processes)
	{
		if (execution_plan->commands[i]->heredoc != NULL)
		{
			g_env_exit = execute_heredocs(*execution_plan->env,
					execution_plan->commands[i]);
			if (g_env_exit)
				return (-1);
		}
		last_pid = fork();
		if (last_pid == -1)
			break ;
		if (last_pid == 0)
			handle_child_process_execution(execution_plan, pipes, i);
		i++;
	}
	return (last_pid);
}

/**
 * Execute one command without forking
 *
 * @param {t_execution_plan *} execution_plan
 * @param {int **} pipes
 *
 * @return {int}
 */
int	execute_single_without_fork(t_execution_plan *execution_plan, int **pipes)
{
	int	exit_code;

	exit_code = 0;
	if (execution_plan->commands[0]->heredoc != NULL)
		exit_code = execute_heredocs(*execution_plan->env,
				execution_plan->commands[0]);
	if (exit_code)
		return (exit_code);
	return (execute_command(execution_plan, pipes, 0));
}
