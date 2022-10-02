/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:32:32 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/23 13:04:21 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

_Bool	is_a_builtins(char *bin)
{
	if (ft_strcmp(bin, "echo") == 0)
		return (true);
	return (false);
}

/**
 *	return -1 if builtin not found
 *	return type of builtin should be unsigned char builtin(command)
 *	this prevent -1 being returned by builtin and misinterpreted by caller
 */
int	execute_builtins(t_command *command)
{
	if (ft_strcmp(command->bin, "echo") == 0)
		return (execute_echo(command));
	return (-1);
}
