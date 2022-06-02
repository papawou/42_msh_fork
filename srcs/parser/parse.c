/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 15:32:30 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/30 16:05:32 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "minishell.h"

/**
 * Count the number of command there is in the commands_as_str argument
 *
 * @param {char **} commands_as_str
 *
 * @return {int} number_of_commands
 */
int	count_number_of_commands(char **commands_as_str)
{
	int		i;

	i = 0;
	while (commands_as_str[i])
		i++;
	return (i);
}

/**
 * Parse a command as string and return an allocated command
 *
 * @param {char *} command_as_str
 *
 * @return {t_command *} command
 */
t_command	*parse_command(char *command_as_str)
{
	char		**arguments;
	t_command	*command;

	command = init_command();
	command_as_str = trim_space(command_as_str);
	arguments = ft_split(command_as_str, ' ');
	arguments = get_io_from_beginning(arguments, command);
	arguments = get_io_from_end(arguments, command);
	command->return_value = 0;
	command->bin = ft_strdup(arguments[0]);
	command = init_command_argv(command, arguments);
	free(command_as_str);
	return (command);
}

/**
 * Parse an entire line and return an allocated execution plan
 *
 * @param {char *} line
 *
 * @return {t_execution_plan *} execution_plan
 */
t_execution_plan	*parse_line(char *line)
{
	int					i;
	t_execution_plan	*execution_plan;
	char				**commands_as_str;
	int					number_of_commands;

	commands_as_str = ft_split(line, '|');
	number_of_commands = count_number_of_commands(commands_as_str);
	execution_plan = init_execution_plan(number_of_commands);
	i = 0;
	while (i < number_of_commands)
	{
		execution_plan->commands[i] = parse_command(commands_as_str[i]);
		i++;
	}
	free(commands_as_str);
	return (execution_plan);
}
