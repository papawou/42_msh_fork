/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:41:13 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/28 18:30:53 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 *
 * @return {unsigned int}
 */
unsigned int	execute_pwd(void)
{
	char			*current_dir;

	current_dir = get_current_dir();
	if (current_dir == NULL)
		return (1);
	printf("%s\n", current_dir);
	free(current_dir);
	return (0);
}
