/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:17:57 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/10 18:40:56 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <stdbool.h>

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
_Bool	route_file_redirect(t_list_el **current_el, int stdstream_fd)
{
	t_file_redirect		*file_redirect;
	t_list_el			*lst_el;

	lst_el = *current_el;
	file_redirect = (t_file_redirect *)lst_el->content;
	file_redirect->file_fd
		= open_file(file_redirect->file, file_redirect->mode);
	if (file_redirect->file_fd < 0)
	{
		*current_el = lst_el->next;
		return (false);
	}
	if (lst_el->next == NULL)
	{
		file_redirect->std_copy = dup(stdstream_fd);
		dup2(file_redirect->file_fd, stdstream_fd);
	}
	else
		close(file_redirect->file_fd);
	*current_el = lst_el->next;
	return (true);
}

_Bool	route_io_linked_list(t_list_el **current_el, int stdstream_fd)
{
	while (*current_el)
	{
		if (!route_file_redirect(current_el, stdstream_fd))
			return (false);
	}
	return (true);
}

/**
 *
 * Redirect stdin and stdout to either pipe or file.
 *
 * @param {t_programs *} execution_plan
 * @param {int **} pipes
 * @param {int} index
 */
_Bool	route_command_io(
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
		if (!route_io_linked_list(&current_el, STDIN_FILENO))
			return (false);
	}
	else if (index != 0)
		dup2(pipes[index][0], STDIN_FILENO);
	close(pipes[index][0]);
	if (command->out != NULL)
	{
		current_el = command->out;
		if (!route_io_linked_list(&current_el, STDOUT_FILENO))
			return (false);
	}
	else if (index != number_of_commands - 1)
		dup2(pipes[index + 1][1], STDOUT_FILENO);
	close(pipes[index + 1][1]);
	return (true);
}
