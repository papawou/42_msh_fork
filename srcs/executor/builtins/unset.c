/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:12:57 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/01 17:19:08 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	execute_unset(t_list_el **env, t_command *command)
{
	int				i;

	i = 1;
	while (command->argv[i])
		remove_environ_el(env, command->argv[i++]);
	return (0);
}
