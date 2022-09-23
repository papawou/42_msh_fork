/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:55:10 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/23 14:24:28 by kmendes          ###   ########.fr       */
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
 * Get list of paths from environment
 *
 * @return {char **} paths
 */
static char	**get_env_paths(void)
{
	char	**paths;
	char	*path_value;

	path_value = get_env_value("PATH");
	paths = ft_split(path_value, ':');
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
static char	*get_path_if_exist(t_command *command)
{
	int		i;
	char	**paths;
	char	*bin;
	char	*bin_path;

	i = 0;
	paths = get_env_paths();
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
static char	*get_program_path(t_command *command)
{
	if (command->bin[0] == '/' || command->bin[0] == '.')
	{
		if (access(command->bin, X_OK) == F_OK)
			return (command->bin);
		else
			return (NULL);
	}
	return (get_path_if_exist(command));
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
	char **fork_environ;

	command = execution_plan->commands[index];
	route_command_io(command, pipes, index, execution_plan->number_of_commands);
	program_path = get_program_path(command);
	if (program_path == NULL)
	{
		perror(program_path);
		exit(-1);
	}
	if (is_a_builtins(command->bin))
		execute_builtins(command);
	fork_environ = t_list_environ_el_to_char_2d(g_environ);
	if (execve(program_path, command->argv, fork_environ) == -1)
	{
		destroy_pipes(execution_plan->number_of_commands, pipes);
		free(program_path);
		free_char_2d(fork_environ);
	}
}

/**
 * Execute the all execution plan by creating, and opening the pipes,
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
