/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:21:28 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/11 14:28:45 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

/**
 *
 * @param {t_list_el **} env
 *
 * @return {unsigned int}
 */
unsigned int	execute_env(t_list_el **env)
{
	char	**environ_char_2d;

	environ_char_2d = environ_el_to_char_2d(*env);
	if (environ_char_2d == NULL)
		return (1);
	print_environ_char_2d(environ_char_2d);
	free_environ_char_2d(environ_char_2d);
	return (0);
}
