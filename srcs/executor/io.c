/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:17:57 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/26 20:34:54 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>

/**
 *
 * Redirect stdin and stdout to either pipe or file.
 *
 * @param {t_programs *} execution_plan
 * @param {int **} pipes
 * @param {int} index
 */
void	route_back_command_io(t_command *command)
{
	if (command->in != NULL)
	{
		close(command->in->file_fd);
		dup2(command->in->std_copy, STDIN_FILENO);
		close(command->in->std_copy);
	}
	if (command->out != NULL)
	{
		close(command->out->file_fd);
		dup2(command->out->std_copy, STDOUT_FILENO);
		close(command->out->std_copy);
	}
}

/**
 *
 * Redirect stdin and stdout to either pipe or file.
 *
 * @param {t_programs *} execution_plan
 * @param {int **} pipes
 * @param {int} index
 */
void	route_command_io(
		t_command *command,
		int **pipes,
		int index,
		int number_of_commands
)
{
	if (command->in != NULL)
	{
		command->in->std_copy = dup(STDIN_FILENO);
		command->in->file_fd = open_file(command->in->file, command->in->mode);
		dup2(command->in->file_fd, STDIN_FILENO);
	}
	else if (index != 0)
		dup2(pipes[index][0], STDIN_FILENO);
	close(pipes[index][0]);
	if (command->out != NULL)
	{
		command->out->std_copy = dup(STDOUT_FILENO);
		command->out->file_fd
			= open_file(command->out->file, command->out->mode);
		dup2(command->out->file_fd, STDOUT_FILENO);
	}
	else if (index != number_of_commands - 1)
		dup2(pipes[index + 1][1], STDOUT_FILENO);
	close(pipes[index + 1][1]);
}
