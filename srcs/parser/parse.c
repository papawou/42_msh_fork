/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:52:45 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/26 20:34:54 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/**
 *
 * @param {char *} line
 *
 * @return {t_execution_plan *}
 */
t_execution_plan	*parse_line(t_list_el *env, char *line)
{
	t_execution_plan	*execution_plan;
	t_list_el			*tokens;
	char				*tmp;

	if (check_quote_closed(line) == false)
	{
		printf("Syntax error, unclosed quote\n");
		free(line);
		return (NULL);
	}
	tmp = trim_space(line);
	line = tmp;
	tmp = ft_strjoin(" ", line);
	line = tmp;
	tmp = ft_strjoin(line, " ");
	free(line);
	line = tmp;
	tokens = tokenize_line(line);
	free(line);
	parse_env_variables(env, tokens);
	execution_plan = parse_all_tokens(tokens->next);
	if (!check_if_need_to_fork(execution_plan))
		execution_plan->need_to_fork = false;
	return (execution_plan);
}
