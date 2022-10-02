/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:55:10 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/25 15:01:28 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

/**
 *
 * Get list of paths from environ
 *
 * @return {char **} paths
 */
static char	**get_env_paths(t_list_el *env)
{
	char	**paths;
	char	*path_value;

	path_value = get_env_value(env, "PATH");
	paths = ft_split(path_value, ':');
	free(path_value);
	return (paths);
}

/**
 *
 * Find the command full path with the PATH env variable.
 * Return null if doesn't exist
 *
 * @param {t_command *} command
 *
 * @return {char *} path
 */
static char	*get_path_if_exist(t_list_el *env, t_command *command)
{
	int		i;
	char	**paths;
	char	*bin;
	char	*bin_path;

	i = 0;
	paths = get_env_paths(env);
	bin = ft_strjoin("/", command->bin);
	while (paths[i])
	{
		bin_path = ft_strjoin(paths[i], bin);
		free(paths[i]);
		if (access(bin_path, X_OK) == F_OK)
			break ;
		else
		{
			free(bin_path);
			bin_path = NULL;
		}
		i++;
	}
	free(bin);
	free(paths);
	return (bin_path);
}

/**
 *
 * Try path for local directory otherwise try PATH variables
 *
 * @param {t_program *} command
 *
 * @return {char *} Program path
 */
static char	*get_program_path(t_list_el *env, t_command *command)
{
	if (command->bin[0] == '/' || command->bin[0] == '.') //is direct path
	{

		if (access(command->bin, X_OK) == F_OK)
		{
			return (ft_strdup(command->bin));
		}
		else
		{
			perror(ft_strjoin("DEBUG: get_program_path: ", command->bin));
			return (ft_strdup(command->bin));
		}
	}
	return (get_path_if_exist(env, command));
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
	int			builtin_ret;

	command = execution_plan->commands[index];
	route_command_io(command, pipes, index, execution_plan->number_of_commands);
	
	program_path = get_program_path(*execution_plan->env, command);
	if (program_path == NULL)
	{
		//perror(program_path);
		return(-1);
	}
	
	builtin_ret = execute_builtins(command);
	if (builtin_ret != -1) // is a builtin
		return (builtin_ret);

	environ_as_arr = environ_el_to_char_2d(*execution_plan->env);
	if (execve(program_path, command->argv, environ_as_arr) == -1)
	{
		int	exit_code;
		exit_code = execve_process_error(program_path, errno);
		free(program_path);
		free_environ_char_2d(environ_as_arr);
		return(exit_code);
	}
	return (1); //<- not reachable
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
