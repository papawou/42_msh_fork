/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:20:15 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/30 16:04:19 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "minishell.h"

t_command	*init_command_argv(t_command *command, char **arguments)
{
	int		i;
	int		number_or_arguments;

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
	return (command);
}

t_command	*init_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (command == NULL)
		exit(ERR_ALLOCATING_MEMORY);
	command->in = NULL;
	command->out = NULL;
	return (command);
}

t_command	*destroy_command(t_command *command)
{
	int		i;

	i = 0;
	while (command->argv[i])
		free(command->argv[i++]);
	free(command->argv);
	free(command->bin);
	free(command->in);
	free(command->out);
	free(command);
	return (NULL);
}
