/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:55:10 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/30 17:35:05 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

/**
 *
 * Get list of paths from environment
 *
 * @return {char **} Paths
 */
static char	**get_env_paths(void)
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	while (paths == NULL)
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
			paths = ft_split((environ[i] + 5), ':');
		else
			i++;
	}
	return (paths);
}

/**
 *
 * Find the command full path with the PATH env variable
 *
 * @param {t_program *} command
 *
 * @return {char *} Program path
 */
static char	*get_program_path(t_command *command)
{
	int		i;
	char	**paths;
	char	*command_path;

	i = 0;
	paths = get_env_paths();
	while (paths[i])
	{
		command_path = ft_strjoin(paths[i], command->path);
		free(paths[i]);
		if (access(command_path, X_OK) == F_OK)
			break ;
		else
		{
			free(command_path);
			command_path = NULL;
		}
		i++;
	}
	free(paths);
	return (command_path);
}

/**
 *
 * Redirect stdin and stdout to either pipe or file.
 *
 * @param {t_programs *} execution_plan
 * @param {int **} pipes
 * @param {int} index
 */
static void	route_command_io(
		t_command *command,
		int **pipes,
		int index,
		int number_of_commands
		)
{
	int			infile_fd;
	int			outfile_fd;

	if (command->in != NULL)
	{
		infile_fd = open_file(command->in, O_RDONLY);
		dup2(infile_fd, STDIN_FILENO);
	}
	else if (index != 0)
		dup2(pipes[index][0], STDIN_FILENO);
	close(pipes[index][0]);
	if (command->out != NULL)
	{
		outfile_fd = open_file(command->out, O_WRONLY | O_CREAT | O_TRUNC);
		dup2(outfile_fd, STDOUT_FILENO);
	}
	else if (index != number_of_commands - 1)
		dup2(pipes[index + 1][1], STDOUT_FILENO);
	close(pipes[index + 1][1]);
}

void	execute_command(
			t_execution_plan *execution_plan,
			int **pipes,
			int index
		)
{
	char		*program_path;
	t_command	*command;

	command = execution_plan->commands[index];
	route_command_io(command, pipes, index, execution_plan->number_of_commands);
	program_path = get_program_path(command);
	if (program_path == NULL)
	{
		perror(program_path);
		exit(-1);
	}
	if (execve(program_path, command->argv, environ) == -1)
	{
		destroy_pipes(execution_plan->number_of_commands, pipes);
		free(program_path);
	}
}

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
