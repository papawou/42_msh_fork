/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:52:45 by fvarrin           #+#    #+#             */
/*   Updated: 2022/07/09 18:17:06 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <stdbool.h>

t_execution_plan	*parse_line(char *line)
{
	t_execution_plan	*execution_plan;
	t_list_el			*tokens;
	char				*tmp;

	if (check_quote_closed(line) == false)
	{
		ft_printf("Syntax error, unclosed quote\n");
		return (NULL);
	}
	execution_plan = init_execution_plan();
	tmp = trim_space(line);
	line = tmp;
	tmp = ft_strjoin(" ", line);
	line = tmp;
	tokens = tokenize_line(line);
	(void) tokens;
	return (execution_plan);
}
