/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:52:45 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/24 19:07:23 by kmendes          ###   ########.fr       */
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
t_execution_plan	*parse_line(t_list_el *env, char *line)
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
	parse_env_variables(env, tokens);
	execution_plan = parse_tokens(tokens->next);
	return (execution_plan);
}
