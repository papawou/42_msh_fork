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

unsigned int	execute_exit(t_command *command)
{
	int		exit_status;

	printf("exit\n");
	if (command->argv[1] && command->argv[2])
	{
		print_exit_error();
		return (1);
	}
	exit_status = 0;
	if (command->argv[1])
		exit_status = ft_atoi(command->argv[1]);
	exit(exit_status);
}
