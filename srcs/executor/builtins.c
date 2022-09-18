/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:32:32 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/18 15:56:50 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>

_Bool	is_a_builtins(char *bin)
{
	if (ft_strcmp(bin, "echo") == 0)
		return (true);
	return (false);
}

void	execute_builtins(t_command *command)
{
	if (ft_strcmp(command->bin, "echo") == 0)
		execute_echo(command);
}
