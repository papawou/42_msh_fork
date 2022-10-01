/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:21:28 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/01 17:26:46 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	execute_env(t_list_el **env)
{
	char	**environ_char_2d;

	environ_char_2d = environ_el_to_char_2d(*env);
	print_environ_char_2d(environ_char_2d);
	return (0);
}
