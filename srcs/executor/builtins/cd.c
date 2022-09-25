/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:32:54 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/26 20:34:54 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	execute_cd(t_list_el *env, t_command *command)
{
	int		status;

	if (command->argv[2] != NULL)
	{
		printf("cd: too many arguments\n");
		return ;
	}
	if (command->argv[1])
		status = chdir(command->argv[1]);
	else
		status = chdir(get_env_value(env, "HOME"));
	if (status != 0)
		perror(command->argv[1]);
}
