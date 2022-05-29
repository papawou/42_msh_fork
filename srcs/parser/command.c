/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:20:15 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/29 16:49:16 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <stdlib.h>

#include "minishell.h"

t_command	*init_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (command == NULL)
		exit(ERR_ALLOCATING_MEMORY);
	return (command);
}

t_command	*destroy_command(t_command *command)
{
	int		i;

	i = 0;
	while (command->argv[i])
		free(command->argv[i++]);
	free(command->argv);
	free(command->path);
	free(command);
	return (NULL);
}