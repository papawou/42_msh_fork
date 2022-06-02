/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:02:35 by fvarrin           #+#    #+#             */
/*   Updated: 2022/06/02 14:48:33 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#include "libft.h"
#include "minishell.h"

/**
 * Set the command input
 *
 * @param {t_command *} command
 * @param {char *} file_name
 *
 * @return {t_command *} command
 */
t_command	*set_input(t_command *command, char *file_name)
{
	command->in = ft_strdup(file_name);
	return (command);
}

/**
 * Set the command output
 *
 * @param {t_command *} command
 * @param {char *} file_name
 * @param {_Bool} append_mode
 *
 * @return {t_command *} command
 */
t_command	*set_output(t_command *command, char *file_name, _Bool append_mode)
{
	command->out = ft_strdup(file_name);
	command->out_in_append_mode = append_mode;
	return (command);
}

t_command	*handle_operator(t_command *command, char **argument)
{
	if (ft_strcmp(*argument, ">") == 0)
		set_output(command, *(argument + 1), false);
	else if (ft_strcmp(*argument, ">>") == 0)
		set_output(command, *(argument + 1), true);
	else if (ft_strcmp(*argument, "<") == 0)
		set_input(command, *(argument + 1));
	return (command);
}

/**
 * If there is an infile in the beginning of the command, set the in property
 * and update arguments accordingly
 *
 * @param {char **} arguments
 * @param {t_command *} command
 *
 * @return {char **} arguments
 */
char	**get_io_from_beginning(char **arguments, t_command *command)
{
	int		i;
	int		args_begin;

	if (ft_strcmp(arguments[0], "<") != 0)
		return (arguments);
	command->in = ft_strdup(arguments[1]);
	i = 2;
	args_begin = i;
	while (--i >= 0)
	{
		free(arguments[i]);
		arguments[i] = NULL;
	}
	return (&arguments[args_begin]);
}

/**
 * If there is an infile or and outfile in the end of the command
 * set the in and / or out properties and update arguments accordingly
 *
 * @param {char **} arguments
 * @param {t_command *} command
 *
 * @return {char **} arguments
 */
char	**get_io_from_end(char **arguments, t_command *command)
{
	int		i;

	i = 0;
	while (arguments[i] && ft_strcmp(arguments[i], "<") != 0
		&& ft_strcmp(arguments[i], ">") != 0
		&& ft_strcmp(arguments[i], ">>") != 0)
		i++;
	if (arguments[i] == NULL)
		return (arguments);
	handle_operator(command, &arguments[i]);
	while (arguments[i])
	{
		handle_operator(command, &arguments[i]);
		free(arguments[i]);
		arguments[i] = NULL;
		i++;
	}
	return (arguments);
}
