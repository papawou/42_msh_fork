/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 16:12:26 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/11 14:43:39 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>
#include <stdlib.h>

unsigned int	execute_export_without_arguments(t_list_el **env)
{
	char	**char_2d;

	char_2d = environ_el_to_char_2d_export(*env);
	print_environ_char_2d(char_2d);
	free_environ_char_2d(char_2d);
	return (0);
}

/**
 *
 * @param {t_list_el **} env
 * @param {t_command *} command
 *
 * @return {unsigned int}
 */
unsigned int	execute_export(t_list_el **env, t_command *command)
{
	int		i;
	_Bool	has_an_error;

	has_an_error = false;
	i = 1;
	if (command->argv[1] == NULL)
		return (execute_export_without_arguments(env));
	while (command->argv[i])
	{
		if (!is_valid_key_value_env(command->argv[i], false))
		{
			has_an_error = true;
			print_custom_error("export",
				command->argv[i], "not a valid identifier");
		}
		else
			add_environ_el(env, command->argv[i]);
		++i;
	}
	if (has_an_error)
		return (1);
	return (0);
}
