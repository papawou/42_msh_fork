/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:17:57 by fvarrin           #+#    #+#             */
/*   Updated: 2022/06/06 17:20:12 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <fcntl.h>
#include <unistd.h>

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
		if (command->out_in_append_mode)
			outfile_fd = open_file(command->out, O_WRONLY | O_CREAT | O_APPEND);
		else
			outfile_fd = open_file(command->out, O_WRONLY | O_CREAT | O_TRUNC);
		dup2(outfile_fd, STDOUT_FILENO);
	}
	else if (index != number_of_commands - 1)
		dup2(pipes[index + 1][1], STDOUT_FILENO);
	close(pipes[index + 1][1]);
}
