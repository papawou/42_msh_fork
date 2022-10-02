/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:55:10 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/01 17:30:36 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

/*
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
*/
/**
 *
 * Take a command, set the io routing and execute it
 *
 * @param {t_execution_plan *} execution_plan
 * @param {int **} pipes
 * @param {int} index
 */
int	execute_command(
			t_execution_plan *execution_plan,
			int **pipes,
			int index
		)
{
	char		*program_path;
	t_command	*command;
	char		**environ_as_arr;
	int			builtin_result;

	command = execution_plan->commands[index];
	route_command_io(command, pipes, index, execution_plan->number_of_commands);
	
	if (command->bin == NULL)
	{
		route_back_command_io(command);
		return (42);
	}
	if (is_a_builtins(command->bin))
	{
		builtin_result = execute_builtins(execution_plan->env, command);
		if (execution_plan->need_to_fork)
			exit(builtin_result);
		route_back_command_io(command);
		return (42);
	}

	program_path = get_program_path(*execution_plan->env, command);
	if (program_path == NULL)
	{
		print_erno_error(NULL);
		exit(-1);
	}

	environ_as_arr = environ_el_to_char_2d(*execution_plan->env);
	if (execve(program_path, command->argv, environ_as_arr) == -1)
	{
		int	exit_code;
		exit_code = execve_process_error(program_path, errno);
		free(program_path);
		free_environ_char_2d(environ_as_arr);
		return(exit_code);
	}
	return (2);
}

int	wait_execute_plan(t_execution_plan *plan, int last_pid)
{
	int wait_ret;
	int	wait_stat;

	(void) plan;
	(void) last_pid;
	while (1)
	{
		wait_ret = wait(&wait_stat);
		if (wait_ret == -1)
		{
			if (errno == ECHILD)
				break ;
			break ; //== EINTR <- this should not be fired
		}
		if (last_pid == wait_ret) //1 is used for debug, in prod replace with "last_pid == wait_ret"
		{
			if (WIFSIGNALED(wait_stat))
			{ printf("DEBUG: %d: child_sign: 128 + %d\n", wait_ret, WTERMSIG(wait_stat));
				return (128 + WTERMSIG(wait_stat));
			}
			else if (WIFEXITED(wait_stat))
			{ printf("DEBUG: %d: child_exit: %d\n", wait_ret, WEXITSTATUS(wait_stat));
				return (WEXITSTATUS(wait_stat));
			}
			printf("DEBUG: child exited not monitored\n");
			return (3);
		}
	}
	return (0);
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
	static int	last_exit = 0;
	int			last_pid;
	int			**pipes;
	int			number_of_child_processes;

	number_of_child_processes = execution_plan->number_of_commands;
	pipes = create_pipes(number_of_child_processes);
	if (pipes == NULL)
	{
		last_exit = 2;
		return (ERR_PIPING | ERR_ALLOCATING_MEMORY);
	}
	last_pid = create_processes(execution_plan, pipes);
	close_pipes_in_main_process(pipes, number_of_child_processes);
	last_exit = wait_execute_plan(execution_plan, last_pid);
	destroy_pipes(number_of_child_processes, pipes);
	return (last_exit);
}
