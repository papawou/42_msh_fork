/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:41:13 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/26 20:41:13 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void	execute_pwd(void)
{
	char			*current_dir;

	current_dir = get_current_dir();
	printf("%s\n", current_dir);
	free(current_dir);
}
