/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:17:57 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/01 14:42:21 by fvarrin          ###   ########.fr       */
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
	t_file_redirect		*in;
	t_file_redirect		*out;

	if (command->in != NULL)
	{
		in = ft_lstlast(command->in)->content;
		close(in->file_fd);
		dup2(in->std_copy, STDIN_FILENO);
		close(in->std_copy);
	}
	if (command->out != NULL)
	{
		out = ft_lstlast(command->out)->content;
		close(out->file_fd);
		dup2(out->std_copy, STDOUT_FILENO);
		close(out->std_copy);
	}
}

/**
 *
 * Open the file and if is last one, dup the file descriptor with stdstream_fd
 * otherwise, close it.
 * Go to next current_el at the end
 *
 * @param {t_list_el **} current_el
 * @param {int} stdstream_fd
 */
void	route_file_redirect(t_list_el **current_el, int stdstream_fd)
{
	t_file_redirect		*file_redirect;
	t_list_el			*lst_el;

	lst_el = *current_el;
	file_redirect = (t_file_redirect *)lst_el->content;
	file_redirect->file_fd
		= open_file(file_redirect->file, file_redirect->mode);
	if (lst_el->next == NULL)
	{
		file_redirect->std_copy = dup(stdstream_fd);
		dup2(file_redirect->file_fd, stdstream_fd);
	}
	else
		close(file_redirect->file_fd);
	*current_el = lst_el->next;
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
	t_list_el	*current_el;

	if (command->in != NULL)
	{
		current_el = command->in;
		while (current_el)
			route_file_redirect(&current_el, STDIN_FILENO);
	}
	else if (index != 0)
		dup2(pipes[index][0], STDIN_FILENO);
	close(pipes[index][0]);
	if (command->out != NULL)
	{
		current_el = command->out;
		while (current_el)
			route_file_redirect(&current_el, STDOUT_FILENO);
	}
	else if (index != number_of_commands - 1)
		dup2(pipes[index + 1][1], STDOUT_FILENO);
	close(pipes[index + 1][1]);
}
