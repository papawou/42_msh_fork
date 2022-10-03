/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:37:43 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/01 17:47:10 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>

void	print_exit_error(void)
{
	ft_printf_fd(
		STDERR_FILENO,
		"%s: exit: too many arguments\n",
		SHELL_NAME
		);
}

unsigned int	execute_exit(t_command *command, t_list_el **env)
{
	int		exit_status;
	int		i;

	printf("exit\n");
	if (command->argv[1] && command->argv[2])
	{
		print_exit_error();
		exit(1);
	}
	if (command->argv[1] == NULL)
	{
		if (env)
			exit(ft_atoi(get_env_value(*env, "?")));
		else
			exit(0);
	}
	exit_status = 0;
	i = 0;
	if (command->argv[1][i] == '+' || command->argv[1][i] == '-')
		++i;
	while (ft_isdigit(command->argv[1][i]))
		++i;
	if (command->argv[1][i] == 0)
		exit_status = ft_atoi(command->argv[1]);
	else
		exit (128);
	if (exit_status < 0)
		exit(255);
	exit(exit_status % 256);
}
