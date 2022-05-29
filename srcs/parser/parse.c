/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 15:32:30 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/29 16:37:19 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

int	count_number_of_commands(char **commands_str)
{
	int		i;

	i = 0;
	while (commands_str[i])
		i++;
	return (i);
}

t_command	*parse_command(char *command_str)
{
	char		*command_str_trimmed;
	char		**arguments;
	int			i;
	int			number_or_arguments;
	t_command	*command;

	command = init_command();
	command_str_trimmed = trim_space(command_str);
	arguments = ft_split(command_str_trimmed, ' ');
	command->path = ft_strdup(arguments[0]);
	command->return_value = 0;
	i = 0;
	number_or_arguments = 0;
	while (arguments[i++])
		number_or_arguments++;
	command->argv = (char **)malloc(sizeof(char *) * (number_or_arguments + 1));
	if (command->argv == NULL)
		exit(ERR_ALLOCATING_MEMORY);
	i = 0;
	while (i < number_or_arguments)
	{
		command->argv[i] = ft_strdup(arguments[i]);
		free(arguments[i]);
		i++;
	}
	command->argv[i] = NULL;
	free(arguments);
	free(command_str_trimmed);
	return (command);
}

t_execution_plan	*parse_line(char *line)
{
	int					i;
	t_execution_plan	*execution_plan;
	char				**commands_str;
	int					number_of_commands;

	commands_str = ft_split(line, '|');
	number_of_commands = count_number_of_commands(commands_str);
	execution_plan = init_execution_plan(number_of_commands);
	i = 0;
	while (i < number_of_commands)
	{
		execution_plan->commands[i] = parse_command(commands_str[i]);
		i++;
	}
	free(commands_str);
	return (execution_plan);
}