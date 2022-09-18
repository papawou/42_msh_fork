/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:52:45 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/18 14:30:46 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>
#include <stdio.h>

/**
 *
 * @param {char *} line
 *
 * @return {t_execution_plan *}
 */
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
	parse_env_variables(tokens);
	execution_plan = parse_tokens(tokens->next);
	return (execution_plan);
}
