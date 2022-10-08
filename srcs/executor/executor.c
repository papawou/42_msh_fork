/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:55:10 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/08 17:19:09 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

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

	command = execution_plan->commands[index];
	route_command_io(command, pipes, index, execution_plan->number_of_commands);
	if (command->bin == NULL)
	{
		route_back_command_io(command);
		return (0);
	}
	if (is_a_builtins(command->bin))
		return (handle_builtins_execution(execution_plan, command));
	program_path = find_program_path(execution_plan, command);
	if (program_path == NULL)
		return (127);
	environ_as_arr = environ_el_to_char_2d(*execution_plan->env);
	if (execve(program_path, command->argv, environ_as_arr) == -1)
		return (clear_if_exec_fail(
				execution_plan, pipes, program_path, environ_as_arr));
	return (2);
}

/**
 *
 * Wait until last_pid process is finished and return
 * the status code of the last process
 *
 * @param last_pid
 *
 * @return {int} status_code
 */
int	wait_execute_plan(int last_pid)
{
	int	status_code;
	int	wait_ret;
	int	wait_stat;

	status_code = 0;
	while (FOREVER)
	{
		wait_ret = wait(&wait_stat);
		if (wait_ret == -1)
		{
			if (errno == ECHILD)
				break ;
			print_custom_error("wait_execute_plan", "wait", strerror(errno));
		}
		else if (last_pid == wait_ret)
		{
			if (WIFSIGNALED(wait_stat))
				status_code = (128 + WTERMSIG(wait_stat));
			else if (WIFEXITED(wait_stat))
				status_code = (WEXITSTATUS(wait_stat));
		}
	}
	return (status_code);
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
	int			last_exit;
	int			last_pid;
	int			**pipes;

	pipes = create_pipes(execution_plan->number_of_commands);
	if (pipes == NULL)
		return (2);
	if (execution_plan->need_to_fork)
		last_pid = create_processes(execution_plan, pipes);
	else
		last_exit = execute_single_without_fork(execution_plan, pipes);
	close_pipes_in_main_process(pipes, execution_plan->number_of_commands);
	if (execution_plan->need_to_fork)
		last_exit = wait_execute_plan(last_pid);
	destroy_pipes(execution_plan->number_of_commands, pipes);
	return (last_exit);
}
