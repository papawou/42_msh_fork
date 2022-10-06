/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:37:43 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/06 17:33:07 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>


/**
 * check if argument is an int, return 0 if success
 **/

static int	check_exit_arg(t_command *command)
{
	int	i;

	i = 0;
	if (command->argv[1][i] == '+' || command->argv[1][i] == '-')
		++i;
	while (ft_isdigit(command->argv[1][i]))
		++i;
	return (command->argv[1][i] != '\0');
}

unsigned int	execute_exit(t_command *command, t_list_el **env)
{
	int		exit_status;

	printf("exit\n");
	if (command->argv[1] && command->argv[2])
	{
		print_custom_error("exit", NULL, "too many arguments");
		exit(2);
	}
	if (command->argv[1] == NULL && env)
		exit(env_exit);
	else if (command->argv[1] == NULL)
		exit(0);
	if (check_exit_arg(command))
	{
		print_custom_error("exit", command->argv[1], "numeric argument required");
		exit (128);
	}
	exit_status = ft_atoi(command->argv[1]);
	if (exit_status < 0)
		exit(255);
	exit(exit_status % 256);
}
