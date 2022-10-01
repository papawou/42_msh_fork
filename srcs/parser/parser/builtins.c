/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:12:33 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/26 20:34:54 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>

_Bool	check_if_need_to_fork(t_execution_plan *execution_plan)
{
	if (execution_plan->number_of_commands > 1)
		return (true);
	if (execution_plan->commands[0]->bin == NULL)
		return (false);
	if (is_a_builtins(execution_plan->commands[0]->bin))
		return (false);
	return (true);
}
