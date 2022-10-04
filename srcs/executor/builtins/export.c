/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 16:12:26 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/01 17:01:19 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>
#include <stdlib.h>

/* upsert added to add_environ_el based on key
static void	add_or_modify_environ_el(t_list_el **env, char *key_value)
{
	char			*key;
	char			*value;
	t_environ_el	*el;

	extract_key_value(key_value, &key, &value);
	el = get_environ_el(*env, key);
	if (el)
	{
		free(el->value);
		el->value = ft_strdup(value);
	}
	else
		add_environ_el(env, key_value);
	free(value);
	free(key);
}
*/

unsigned int	execute_export(t_list_el **env, t_command *command)
{
	int		i;
	_Bool	has_an_error;

	has_an_error = false;
	i = 1;
	while (command->argv[i])
	{
		if (!is_valid_key_value_env(command->argv[i]))
		{
			has_an_error = true;
			print_custom_error("export", command->argv[i], "not a valid identifier");
		}
		else
			add_environ_el(env, command->argv[i]);
		++i;
	}
	if (has_an_error)
		return (1);
	return (0);
}
