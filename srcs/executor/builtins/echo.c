/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:36:50 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/28 18:26:50 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdbool.h>

unsigned int	execute_echo(t_command *command)
{
	_Bool	without_line_break;
	int		i;

	without_line_break = false;
	i = 1;
	if (command->argv[i] && ft_strcmp(command->argv[i], "-n") == 0)
	{
		without_line_break = true;
		i++;
	}
	while (command->argv[i])
	{
		printf("%s", command->argv[i++]);
		if (command->argv[i])
			printf(" ");
	}
	if (!without_line_break)
		printf("\n");
	return (0);
}
