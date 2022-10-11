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

#include <stdbool.h>

/**
 *
 * @param {t_list_el **} env
 * @param {t_command *} command
 *
 * @return {unsigned int}
 */
unsigned int	execute_unset(t_list_el **env, t_command *command)
{
	int				i;
	_Bool			has_an_error;

	has_an_error = false;
	i = 1;
	while (command->argv[i])
	{
		if (!is_valid_key_value_env(command->argv[i]))
		{
			has_an_error = true;
			print_custom_error("unset",
				command->argv[i++], "not a valid identifier");
		}
		else
			remove_environ_el(env, command->argv[i++]);
	}
	if (has_an_error)
		return (1);
	return (0);
}
