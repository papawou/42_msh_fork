/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:55:10 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/26 20:54:33 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

static void	clear_if_exec_fail(
		t_execution_plan *execution_plan,
		int **pipes,
		char *program_path,
		char **environ_as_arr
	)
{
	destroy_pipes(execution_plan->number_of_commands, pipes);
	free(program_path);
	ft_lstclear(execution_plan->env, &destroy_environ_el);
	free_environ_char_2d(environ_as_arr);
	exit(127);
}

/**
 *
 * Take a command, set the io routing and execute it
 *
 * @param {t_execution_plan *} execution_plan
 * @param {int **} pipes
 * @param {int} index
 */
void	execute_command(
			t_execution_plan *execution_plan,
			int **pipes,
			int index
		)
{
	char		*program_path;
	t_command	*command;
	char		**environ_as_arr;

	command = execution_plan->commands[index];
	route_command_io(command, pipes, index, execution_plan->number_of_commands);
	if (is_a_builtins(command->bin))
	{
		execute_builtins(*(execution_plan->env), command);
		route_back_command_io(command);
		return ;
	}
	program_path = get_program_path(*execution_plan->env, command);
	if (program_path == NULL)
	{
		perror(program_path);
		exit(-1);
	}
	environ_as_arr = environ_el_to_char_2d(*execution_plan->env);
	if (execve(program_path, command->argv, environ_as_arr) == -1)
		clear_if_exec_fail(execution_plan, pipes, program_path, environ_as_arr);
}

/**
 * Execute the full execution plan by creating, and opening the pipes,
 * forking for each command, closing the unnecessary pipes and in each child
 * process executing the command
 *
 * @param {t_execution_plan *} execution_plan
 * @return
 */
int	execute_plan(t_execution_plan *execution_plan)
{
	int			i;
	int			*pids;
	int			**pipes;
	int			number_of_child_processes;

	number_of_child_processes = execution_plan->number_of_commands;
	pipes = NULL;
	pids = NULL;
	pipes = create_pipes(number_of_child_processes, pipes);
	pids = create_processes(execution_plan, pids, pipes);
	i = 0;
	close_pipes_in_main_process(pipes, number_of_child_processes);
	while (i < number_of_child_processes)
	{
		waitpid(pids[i], &(execution_plan->commands[i]->return_value), 0);
		if (WEXITSTATUS(execution_plan->commands[i]->return_value) != 0)
			exit(WEXITSTATUS(execution_plan->commands[i]->return_value));
		i++;
	}
	destroy_pipes(number_of_child_processes, pipes);
	free(pids);
	return (0);
}
