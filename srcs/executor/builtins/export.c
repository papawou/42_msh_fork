/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 16:12:26 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/01 16:43:59 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>

void	print_export_error(char *identifier)
{
	ft_printf_fd(
		STDERR_FILENO,
		"%s: export: `%s`: not a valid identifier\n",
		SHELL_NAME,
		identifier
		);
}

unsigned int	execute_export(t_list_el **env, t_command *command)
{
	int		i;
	_Bool	has_an_error;

	has_an_error = false;
	i = 1;
	while (command->argv[i])
	{
		if (!is_valid_key_value_env(command->argv[i], true))
		{
			has_an_error = true;
			print_export_error(command->argv[i++]);
			continue ;
		}
		add_environ_el(env, command->argv[i++]);
	}
	if (has_an_error)
		return (1);
	return (0);
}
