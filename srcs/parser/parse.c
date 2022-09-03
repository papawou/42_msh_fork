/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:52:45 by fvarrin           #+#    #+#             */
/*   Updated: 2022/07/17 12:40:12 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>
#include <stdio.h>

t_execution_plan	*parse_line(char *line)
{
	t_execution_plan	*execution_plan;
	t_list_el			*tokens;
	char				*tmp;

	if (check_quote_closed(line) == false)
	{
		printf("Syntax error, unclosed quote\n");
		return (NULL);
	}
	tmp = trim_space(line);
	line = tmp;
	tmp = ft_strjoin(" ", line);
	line = tmp;
	tmp = ft_strjoin(line, " ");
	line = tmp;
	tokens = tokenize_line(line);
	// Expand env variable from token here
	execution_plan = parse_tokens(tokens->next);
	return (execution_plan);
}
