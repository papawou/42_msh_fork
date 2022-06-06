/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 15:32:30 by fvarrin           #+#    #+#             */
/*   Updated: 2022/06/06 14:41:40 by fvarrin          ###   ########.fr       */
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
	t_list_el	*words;
	t_command	*command;

	command = init_command();
	words = command->words;
	command_as_str = trim_space(command_as_str);
	words = split_into_words(words, command_as_str);
	words = get_io_from_words(words, command);
	command->return_value = 0;
	command->bin = ft_strdup(((t_token *)words->content)->word);
	command->words = words;
	init_command_argv(command);
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
