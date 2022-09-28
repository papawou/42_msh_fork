/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:32:32 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/28 18:30:20 by fvarrin          ###   ########.fr       */
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
	if (ft_strcmp(bin, "cd") == 0)
		return (true);
	if (ft_strcmp(bin, "pwd") == 0)
		return (true);
	return (false);
}

/**
 *
 *	return -1 if builtin not found use is_a_builtin() before to avoid this error
 *	return type of builtin should be unsigned int builtin()
 *	this prevent -1 being returned by builtin and misinterpreted by caller
 *
 * @param {t_command *} command
 *
 * @return {int}
 */
int	execute_builtins(t_list_el *env, t_command *command)
{
	if (ft_strcmp(command->bin, "echo") == 0)
		return (execute_echo(command));
	if (ft_strcmp(command->bin, "cd") == 0)
		return (execute_cd(env, command));
	if (ft_strcmp(command->bin, "pwd") == 0)
		return (execute_pwd());
	return (-1);
}
